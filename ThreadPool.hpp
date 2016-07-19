/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ThreadPool.hpp
 * Author: matthewsupernaw
 *
 * Created on July 19, 2016, 11:24 AM
 */

#ifndef THREADPOOL_HPP
#define THREADPOOL_HPP

#include <thread>
#include <atomic>
#include <condition_variable>
#include <queue>
#include <vector>
#include <future>


namespace noaa {
    namespace mas {
        
    class ThreadPool {
    public:

        ThreadPool(int threads = std::thread::hardware_concurrency()) : shutdown_(false) {
            // Create the specified number of threads
            threads_.reserve(threads);
            for (int i = 0; i < threads; ++i)
                threads_.emplace_back(std::bind(&ThreadPool::threadEntry, this, i));
        }

        ~ThreadPool() {
            {
                // Unblock any threads and tell them to stop
                std::unique_lock <std::mutex> l(lock_);

                shutdown_ = true;
                condVar_.notify_all();
            }

            // Wait for all threads to stop
            for (auto& thread : threads_)
                thread.join();
        }

        size_t Size() {
            return threads_.size();
        }

        void doJob(std::function <void (void) > func, bool put_in_wait_list = true) {
            if (put_in_wait_list) {
                this->wait_count++;
            }
            // Place a job on the queue and unblock a thread
            std::unique_lock <std::mutex> l(lock_);
            jobs_.emplace(std::make_pair(std::move(func), put_in_wait_list));
            condVar_.notify_one();
        }

        void wait() {
            while (this->wait_count != 0) {
                //wait for threads
            }
  
        }



    protected:

        void threadEntry(int i) {
            std::pair < std::function <void (void) >, bool> job_;

            while (1) {
                {
                    std::unique_lock <std::mutex> l(lock_);

                    while (!shutdown_ && jobs_.empty())
                        condVar_.wait(l);

                    if (jobs_.empty()) {
                        // No jobs to do and we are shutting down
                        return;
                    }

                    job_ = std::move(jobs_.front());
                    jobs_.pop();
                }

                // Do the job without holding any locks
                std::function <void (void) > task = job_.first;


                if (job_.second) {
                    task();
                     wait_count--;
                } else {
                    task();
                }
            }

        }


        std::mutex lock_;
        std::condition_variable condVar_;
        bool shutdown_;
        std::queue <std::pair<std::function <void (void) >, bool> > jobs_;
        std::vector <std::thread> threads_;
        std::atomic<int> wait_count;
    };

    }
}

#endif /* THREADPOOL_HPP */

