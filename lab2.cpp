//#include <eh.h>
//#include <memory>
//#include <stdexcept>
//#include <signal.h>
#include <csignal>
 
#include <windows.h>
#include <winnt.h> //EXCEPTION_POINTERS

#include <string>
#include <vector>
#include <Psapi.h>
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <iterator>


#include <iostream>
#include <string>
 







//Реализуйте метод, который запрашивает у пользователя ввод дробного числа(типа float),
//и возвращает введенное значение.
//Ввод текста вместо числа не должно приводить к падению приложения,
//вместо этого, необходимо повторно запросить у пользователя ввод данных.
float get_fractional_input() {
    float value;
    std::string input_string;

    while (true) {
        std::cout << "Please enter a fractional number: ";
        std::getline(std::cin, input_string);

        try {
            value = std::stof(input_string);
            break;
        }
        catch (...) {
            std::cerr << "Invalid input. Please enter a fractional number." << std::endl;
        }
    }

    return value;
}

inline int DivEx(int numerator, int denominator) {
    if (denominator == 0)
        throw std::overflow_error("Divide by 0");
    return numerator / denominator;
}

inline static void printSum(int a, int b) 
{
    std::cout << (a + b) << std::endl;
}

inline void user_check_empty_input() {
    std::string input;

    std::cout << "Enter string: " << std::endl;
    std::getline(std::cin, input);

    try {
        if (input.empty()) {
            throw std::runtime_error("Input cannot be empty ");
        }
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    } 
}


int main()
{

    float value = get_fractional_input(); 

    // Задание 2

    //описание https://stackoverflow.com/questions/6121623/catching-exception-divide-by-zero 
    //tracktrace  https://stackoverflow.com/questions/15372962/in-the-handler-of-setunhandledexceptionfilter-how-to-print-a-stacktrace
            // https://github.com/Furkanzmc/ExceptionHandler/

    //Целочисленное деление на ноль не является исключением в стандартном C++

    //Разыменование нулевых указателей, деление на ноль и т.д.не создает исключений в C++, это приводит к неопределенному поведению.
    //Если вы хотите, чтобы исключения вызывались в таких случаях, вы должны вручную обнаружить эти условия и сделать throw явно.
   
    int intArray[8] = { 0, 1, 2, 3, 4, 5, 6, 7 };
    int d = 0;
    try {        
        double catchedRes1 = DivEx(intArray[7],d);
        std::cout << "catchedRes1 = " << catchedRes1 << std::endl;
    } catch (std::overflow_error  e)
    {
        std::cerr << e.what() << std::endl;
    }
     
    // Задание 3
  
    try {
        int a = 90;
        int b = 3;
        std::cout << DivEx(a, b);
        printSum(23, 234);
        int abc[2] = { 1, 2 };
        int setted_by_index = 3;
        if (setted_by_index  < 0 || setted_by_index  > (sizeof(abc)-1))//в данном конктретном случае!
            throw std::out_of_range("Index Out Of Bounds");
        abc[setted_by_index] = 9;
    }
    catch (std::overflow_error& e)
    {
        std::cerr << e.what() << std::endl;
    }
    catch (std::out_of_range& e)
    {
        std::cerr << e.what() << std::endl;
    }
    catch (...) //c null вообще делай что хочень это с++.
    {
        std::cerr << "some error " << std::endl;
    }  

    // Задание 4 
    // Разработайте программу, которая выбросит Exception, когда пользователь вводит пустую строку.
    // Пользователю должно показаться сообщение, что пустые строки вводить нельзя.
    user_check_empty_input();

}