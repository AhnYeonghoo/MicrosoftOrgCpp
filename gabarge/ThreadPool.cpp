#include <iostream>
#include <chrono>
#include <condition_variable>
#include <cstdio>
#include <functional>
#include <mutex>
#include <thread>
#include <vector>
#include <queue>

namespace ThreadPool
{
	class ThreadPool
	{
	public:
		ThreadPool(size_t num_threads);
		~ThreadPool();
		
		// Job을 추가한다.
		void EnqueueJob(std::function<void()> job);

	private:
		// 총 Worker 쓰레드 개수
		size_t num_threads_;
		// Worker 쓰레드를 보관하는 벡터
		std::vector<std::thread> worker_threads_;
		// 할일들을 보관하는 job 큐
		std::queue<std::function<void()>> jobs_;
		//위의 job 큐를 위한 cv와 m.
		std::condition_variable cv_job_q_;
		std::mutex m_job_q_;

		// 모든 쓰레드 종료
		bool stop_all_;

		// Worker 쓰레드
		void WorkerThread();

	};

	ThreadPool::ThreadPool(size_t num_threads)
		: num_threads_(num_threads), stop_all_(false)
	{
		worker_threads_.reserve(num_threads_);
		for (size_t i = 0; i < num_threads_; i++)
		{
			worker_threads_.emplace_back([this]() {this->WorkerThread(); });
		}
	}

	void ThreadPool::WorkerThread()
	{
		while (true)
		{
			std::unique_lock<std::mutex> lock(m_job_q_);
			cv_job_q_.wait(lock, [this]() { return !this->jobs_.empty() || stop_all_; });
			if (stop_all_ && this->jobs_.empty()) return;

			std::function<void()> job = std::move(jobs_.front());
			jobs_.pop();
			lock.unlock();
			job();
		}
	}

	ThreadPool::~ThreadPool()
	{
		stop_all_ = true;
		cv_job_q_.notify_all();

		for (auto& t : worker_threads_)
		{
			t.join();
		}
	}

	void ThreadPool::EnqueueJob(std::function<void()> job)
	{
		if (stop_all_)
		{
			throw std::runtime_error("ThreadPool 사용 중지됨");
		}
		{
			std::lock_guard<std::mutex> lock(m_job_q_);
			jobs_.push(std::move(job));
		}
		cv_job_q_.notify_one();
	}
}

void work(int t, int id)
{
	printf("%d start \n", id);
	std::this_thread::sleep_for(std::chrono::seconds(t));
	printf("%d end after %ds\n", id, t);
}

int mainThreadPool()
{
	ThreadPool::ThreadPool pool(3);

	for (int i = 0; i < 10; i++)
	{
		pool.EnqueueJob([i]() {work(i % 3 + 1, i); });
	}

	return 0;
}