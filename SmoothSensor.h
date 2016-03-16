#ifndef _SMOOTHSENSOR_H
#define _SMOOTHSENSOR_H

/*
	This generic class helps stabilize readings from an analog sensor.
*/
template <class T> class SmoothSensor
{
    private:
		const uint32_t _bufferSize; //number of elements in buffer
		T *_buffer; //the readings from the analog input
		uint32_t _index; //the index of the current reading  
		T _sum; //the running sum

	public:
		SmoothSensor(uint32_t bufferSize); //ctor
		~SmoothSensor(); //dtor
		void push(T reading); //add a reading to buffer
		inline T read(); //read smoothed sensor data
		inline float readfp(); //same as above, with floating point
		T read(T reading); //push reading and read smoothed sensor data
		float readfp(T reading); //same as above, with floating point
};

	template <class T> SmoothSensor<T>::SmoothSensor(uint32_t bufferSize=10)
		: _bufferSize(bufferSize)
	{
		_buffer = (T *)calloc(_bufferSize, sizeof(T));//zeroing values
		_index = 0;
		_sum = 0;  
	}

	template <class T> SmoothSensor<T>::~SmoothSensor()
	{
		free(_buffer);
	}

	template <class T> inline T SmoothSensor<T>::read()
	{
		return _sum / _bufferSize;
	}
	
	template <class T> inline float SmoothSensor<T>::readfp()
	{
		return (float)_sum / _bufferSize;
	}
	
	template <class T> T SmoothSensor<T>::read(T reading)
	{
		push(reading);
		return read();
	}
	
	template <class T> float SmoothSensor<T>::readfp(T reading)
	{
		push(reading);
		return readfp();
	}
	
	template <class T> void SmoothSensor<T>::push(T reading)
	{
		_sum -= _buffer[_index];   // subtract the last reading
		_buffer[_index] = reading;

		_sum += _buffer[_index]; // add the reading to the sum

		if (++_index >= _index)
		{
			_index = 0;
		}
	}

#endif