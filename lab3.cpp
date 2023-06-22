#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include <cctype>
#include <algorithm> //all_of
   
bool is_digits(const std::string& str)
{
    return std::all_of(str.begin(), str.end(), ::isdigit); // C++11
}

int main()
{ 
    // Prompt user for input
    std::cout << "Please enter your surname, date of birth (dd.mm.yyyy), and phone number: ";
    std::string input;
    std::getline(std::cin, input);

    // Split input into parts
    std::istringstream ss(input);
    std::istringstream s1(input);
    std::string surname, str_data, phone_number; 
    int count_str = std::distance(std::istream_iterator<std::string>(s1), std::istream_iterator<std::string>());

    std::ofstream out;

    try
    {
        // проверка количества данных
        if (count_str != 3)
        {
            throw std::logic_error("Invalid count input data given: " + count_str);
        }
        //std::cout << "count_str: " << count_str << std::endl;
        //std::cout << "input: " << input << std::endl;

        ss >> surname >> str_data >> phone_number;


        if (!is_digits(phone_number))
        {
            throw std::logic_error("Not valid phone number: " + phone_number);
        }

        // проверка формата даты 
        int day, month, year;
        char dot1, dot2;
        std::stringstream(str_data) >> day >> dot1 >> month >> dot2 >> year;
        //std::cout << "date: " << day << " " << month << " " << year << " " << std::endl;

        //проверка лимитов даты 
        if (dot1 != '.' ||
            dot2 != '.' ||
            day < 1 || day > 31 ||
            month < 1 || month > 12 ||
            year < -100000 || year > 9999)
        {
            throw std::logic_error("Invalid date of birth:"+ str_data +" enter your date of birth as dd.mm.yyyy");
        }
         
        std::cout << "surname: " << surname << std::endl;
        std::cout << "date of birth: " << str_data << std::endl;
        std::cout << "phone number: " << phone_number << std::endl;

        std::string filename = surname + ".txt";
        
        
        out.open(filename, std::ios::app); // окрываем файл дл¤ дозаписи

        // записываем строку
        if (out.is_open())        
            out << surname << " " << str_data << " " << phone_number << "\n";
        else 
            throw std::runtime_error("file not opened :" + filename);
        out.close();

    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
/*

вариант с некоректной датой рождения 

    Please enter your surname, date of birth(dd.mm.yyyy), and phone number : wd 45.4.4 4554
    Invalid date of birth : 45.4.4 enter your date of birth as dd.mm.yyyy
 
однофамильцы в 1 файле

    Please enter your surname, date of birth (dd.mm.yyyy), and phone number: wd 4.4.42 47944
    surname: wd
    date of birth: 4.4.42
    phone number: 47944
    Please enter your surname, date of birth (dd.mm.yyyy), and phone number: wd 4.4.78 489455
    surname: wd
    date of birth: 4.4.78
    phone number: 489455

содержимое файла с ондофамильцами wd.txt

wd 4.4.42 47944
wd 4.4.78 489455
 
*/