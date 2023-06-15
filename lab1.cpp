// https://tproger.ru/articles/iskljuchenija-v-cpp-tipy-sintaksis-i-obrabotka/
 
#include <iostream>
#include <fstream>
#include <string>
#include <string_view>
#include <vector>

// Собственные исключения
class Exception_my {
public:
	virtual std::string what() const = 0;
};

class File_not_found: public Exception_my {
public:
	std::string what() const override 
	{
		return "file_not_found";
	}
}; 

class Arrays_not_equal: public Exception_my {
public:
	std::string what() const override
	{
		return "Arrays_not_equal";
	}
};


//функции под  вызов исключений

double divide(int a, int b)
{
	//return a / b; //Необработанное исключение : Integer division by zero.
	if (b)
		return a / b;
	//throw "Division by zero!"; //Возникло необработанное исключение по адресу 0x766BD8A2 в lab1.exe
	throw std::string{ "Division by zero!" };
}

void devide_by_zero(int argument) noexcept //метка: функция не может вызвать исключение
{
	//double t = argument / 0;//но если оно есть, вызовет
}
 
void traverseArray(int* arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		//std::cout << arr[i] << " ";
		std::cout << *(arr + i) << " "; 
	}
	std::cout << std::endl;
}


void read_file()
{
	std::string filename = "test.txt";
	std::ifstream infile(filename);

	if (!infile.is_open()) 
	{
		std::cerr << "Error: Could not open file '" << filename << "'\n";
		throw File_not_found();
		
	}

	// File is open, read its content
	std::string line;
	while (std::getline(infile, line)) {
		std::cout << line << '\n';
	}

	infile.close(); 
}

//для 2 задания
std::vector<int> array_diff(std::vector<int>& arr1, std::vector<int>& arr2) 
{
	if (arr1.size() != arr2.size()) 
	{
		std::cout << "Error: array1 length= " << arr1.size()
			<< " not equal array2 length="<< arr2.size() << std::endl;
		return std::vector<int>();
	}

	std::vector<int> diff_arr(arr1.size());

	for (int i = 0; i < arr1.size(); i++) 
		diff_arr[i] = arr1[i] - arr2[i];

	return diff_arr;
}


std::vector<float> array_division(std::vector<int>& arr1, std::vector<int>& arr2)
{
	if (arr1.size() != arr2.size())		
		throw Arrays_not_equal();

	std::vector<float> diff_arr(arr1.size());

	for (int i = 0; i < arr1.size(); i++)
		diff_arr[i] = arr1[i]/arr2[i];
	
	return diff_arr;
}




int main()
{
	devide_by_zero(12);//проверка флага отсутсвия икслючений

	int x= 500;
	int y=0;
	double z = .0;
	try//при возниковени исключения у всех созданных внутри обьектов вызывается деструктор
	{
		z= divide(x, y);
	}
	//catch (...)//перехват всех исключений
	//catch (const char* error_message)// с перехватом сообщения передается копией обьекта иключения
	catch (const std::string& error_message) // строка передается по ссылке
	{ 
		//если вошли через catch (...) обратится к исключению нельзя но можно перебросить его выше  throw; // перебрасываем исключение
		std::cout << error_message << std::endl;
		//std::cout << "Error!" << std::endl;
	}  
	

	int size = 4;
	int* arr = new int[size];
	for (int i = 0; i < size; i++)
		arr[i] = i;	
	//size = sizeof(arr) / sizeof(arr[0]); // длч статики 
	
	// 2 исключение
	try 
	{
		traverseArray(arr, size);
		delete[] arr; 
		arr = NULL; 
		//traverseArray(arr, size); исключение прав доступа к невыделенной памяти
	}
	catch (const std::exception& e)
	{		
		std::cout << " exception: " << e.what() << std::endl;
	}
	 
	// 3 исключение
	try
	{
		read_file();
	}
	catch (Exception_my& e)//при обращении по ссылке не создается копия обьекта исключения 
		// отловить можно всех наслелников Exception_my
	{
		std::cout << " exception: " << e.what() << std::endl;
	}



	// 2 задание
	std::vector<int> a{ 3, 6, 9 };
	std::vector<int> b{ 1, 5, 7 };
	std::vector<int> c = array_diff(a, b);

	for (int i = 0; i < c.size(); i++)
		std::cout << c[i] << " ";

	std::cout << std::endl;

	std::vector<int> d{ 4, 8, 12 };
	std::vector<int> e{ 1, 3, 5, 7 };
	std::vector<int> f = array_diff(d, e);

	for (int i = 0; i < f.size(); i++)
		std::cout << f[i] << " ";

	std::cout << std::endl;

	//2 задание * с моим исключение
	try
	{

		std::vector<float> f = array_division(d, e);

		for (int i = 0; i < f.size(); i++)
			std::cout << f[i] << " ";

		std::cout << std::endl;

	}
	catch (Exception_my& e) 
	{
		std::cout << " exception: " << e.what() << std::endl;
	} 


	std::cout << "end" << std::endl;
	putchar('\n');
	getchar();

	return 0;
}
 
/*
>>>

Division by zero!
0 1 2 3
Error: Could not open file 'test.txt'
exception : file_not_found
2 1 2
Error : array1 length = 3 not equal array2 length = 4

exception : Arrays_not_equal
end
*/
