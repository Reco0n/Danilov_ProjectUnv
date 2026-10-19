#pragma once
#include <iostream>

// Ввод строки с записью в лог (cerr перенаправлен в файл лога)
#define INPUT_LINE(in, str) getline(in>>std::ws, str); \
						std::cerr << str << std::endl

class redirect_output_wrapper
{
	std::ostream& stream;
	std::streambuf* const old_buf;
public:
	redirect_output_wrapper(std::ostream& src)
		:stream(src), old_buf(src.rdbuf())
	{
	}

	~redirect_output_wrapper() {
		stream.rdbuf(old_buf);
	}
	void redirect(std::ostream& dest)
	{
		stream.rdbuf(dest.rdbuf());
	}
};

template <typename T>
T GetCorrectNumber(T min, T max)
{
	T x;
	while ((std::cin >> x).fail()	// проверка типа
		|| std::cin.peek() != '\n'	// в буфере ничего лишнего
		|| x < min || x > max)		// проверка диапазона
	{
		std::cin.clear();
		std::cin.ignore(10000, '\n');
		std::cout << "Введите число (" << min << "-" << max << "): ";
	}
	std::cerr << x << std::endl;
	return x;
}
