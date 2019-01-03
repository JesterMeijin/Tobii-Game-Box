#ifndef TIME_COUNTER_INCLUDED
#define TIME_COUNTER_INCLUDED

namespace core {

	/// This class is used to know if a time as passed
	class TimeCounter
	{
	public:
		/// Initialize the start time with the current time
		TimeCounter(unsigned int activationTimeInMs);
		~TimeCounter() = default;

		/// reset the start time
		/// set the start time to the current time
		void reset();

		/// Return the remaining time for this time counter
		unsigned int getRemainingTime();

		/// return true if the time as passed
		bool isTimePassed();

	private:
		/// the start time
		unsigned int startTime_;

		/// The trigger time
		unsigned int activationTime_;
	};
}

#endif // TIME_COUNTER_INCLUDED