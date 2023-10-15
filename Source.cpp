#include"Auxiliary_Functions.h"
#include<filesystem>
namespace fs = std::filesystem;
struct Page // структура Страница
{
	string Number; // численное значение страницы
	Page* Point_to_Next_Object; // указатель на следующий объект в ветви
	Page(const string& str)// инициализирующий конструктор
	{
		Number = str;
		Point_to_Next_Object = nullptr;
	}
	Page()// конструктор по умолчанию
	{
		Number = "";
		Point_to_Next_Object = nullptr;
	}
};
struct Term // структура Термин
{
	string Name; // название термина
	Term* Point_to_Next_Object; // указатель на следующий объект ствола
	Page* Point_to_Branch; // указатель на первую страницу, где встречается термин
	Term(const string& str) // инициализирующий конструктор
	{
		Name = str;
		Point_to_Branch = nullptr;
		Point_to_Next_Object = nullptr;
	}
	Term() // конструктор по умолчанию
	{
		Name = "";
		Point_to_Branch = nullptr;
		Point_to_Next_Object = nullptr;
	}
};
Term* Beginning_Pointer = nullptr; // указатель на самый первый объект в структуре
bool unsaved_changes = false; // показатель наличия изменений в текущей структуре при работе с ней
//============================================================


void Add_Term(const string& str) // функция добавления элемента в ствол структуры
{
	Term* Current_Trunk_Object; // указатель на текущий добавляемый объект
	Current_Trunk_Object = new Term(str); // инициализация его полей
	if (Beginning_Pointer != nullptr) // если структура данных непустая
	{
		Term* Iterating_Pointer = Beginning_Pointer; // указатель для последовательного просмотра структуры для поиска её конца для добавления объекта
		while (Iterating_Pointer->Point_to_Next_Object != nullptr) // пока указатель на следующий элемент указателя для последовательного просмотра структуры не равен значению пустого указателя
		{
			Iterating_Pointer = Iterating_Pointer->Point_to_Next_Object; // указатель для последовательного просмотра равен указателю на следующий элемент
		}
		Iterating_Pointer->Point_to_Next_Object = Current_Trunk_Object;// указатель на следующий объект в структуре данных теперь указывает на добавленный объект
	}
	else Beginning_Pointer = Current_Trunk_Object; // указатель на первый объект в структуре данных теперь указывает на добавленный объект
}
void Add_Page(const string& Teacher_Name, const string& Name_of_Discipline) // функция добавления элемента в ветвь структуры
{
	Term* Current_Trunk_Object; // указатель на текущий добавляемый объект
	Page* New_Object = new Page(Name_of_Discipline);// инициализация его полей
	Current_Trunk_Object = Beginning_Pointer;
	while (Current_Trunk_Object->Name != Teacher_Name) // пока значение текущего элемента ствола не равно значению введенной строки
	{
		Current_Trunk_Object = Current_Trunk_Object->Point_to_Next_Object; // переставить указатель ствола на следующий элемент
	}
	if (Current_Trunk_Object->Point_to_Branch != nullptr) // если в ветви есть объекты
	{
		Page* Iterating_Pointer = Current_Trunk_Object->Point_to_Branch;
		while (Iterating_Pointer->Point_to_Next_Object != nullptr) // пока указатель на объект ветви непустой
		{
			Iterating_Pointer = Iterating_Pointer->Point_to_Next_Object; // переставить указатель ветви на следующий элемент
		}
		Iterating_Pointer->Point_to_Next_Object = New_Object;// указатель на ветвь объекта ствола равен указателю на новый объект 
	}
	else
	{
		Current_Trunk_Object->Point_to_Branch = New_Object; // указатель на ветвь объекта ствола равен указателю на новый объект 
		New_Object->Point_to_Next_Object = nullptr; // указатель на следующий объект ветви равен пустому указателю
	}
}
string write_to_file_all() // функция записи структуры в файл
{
	ofstream writing_filestream;
	string filename;
	filename = "Предметный указатель за_";
	stringstream torrent;
	time(NULL);
	chrono::zoned_time date_time
	{
		chrono::current_zone(),
		chrono::system_clock::now()
	};
	torrent << format("{:%d.%m.%Y_%H-%M}", date_time);
	string reading_stringstream;
	while (torrent >> reading_stringstream)
	{
		filename += reading_stringstream;
	}
	filename += ".txt";
	writing_filestream.open(filename); // открыть файловый поток на запись 
	Term* Trunk_Current_Object = Beginning_Pointer;
	do
	{
		writing_filestream << Trunk_Current_Object->Name << endl << endl;
		if (Trunk_Current_Object->Point_to_Branch != nullptr)
		{
			Page* Branch_Current_Object = Trunk_Current_Object->Point_to_Branch;
			while (Branch_Current_Object != nullptr)
			{
				writing_filestream << Branch_Current_Object->Number << endl;
				Branch_Current_Object = Branch_Current_Object->Point_to_Next_Object;
			}
		}
		Trunk_Current_Object = Trunk_Current_Object->Point_to_Next_Object;
		writing_filestream << endl << endl;
	} while (Trunk_Current_Object != nullptr);
	writing_filestream.close();
	return filename;
}
void delete_trunk_object(Term*& Current_Object, const string& Teacher_Name)
{
	// функция удаления объекта ствола 
	Term* Temporary = Beginning_Pointer;
	if (Current_Object != Beginning_Pointer)
	{
		while (Temporary->Point_to_Next_Object != Current_Object)
		{
			Temporary = Temporary->Point_to_Next_Object;
		}
	}
	if (Current_Object->Point_to_Branch != nullptr)
	{
		Page* Iterating_Pointer = Current_Object->Point_to_Branch;
		Page* temporary;
		while (Iterating_Pointer->Point_to_Next_Object != nullptr)
		{
			temporary = Iterating_Pointer->Point_to_Next_Object;
			delete Iterating_Pointer;
			Iterating_Pointer = temporary;
		}
	}
	if (Current_Object == Beginning_Pointer)
	{
		Beginning_Pointer = Current_Object->Point_to_Next_Object;
	}
	else
	{
		Temporary->Point_to_Next_Object = Current_Object->Point_to_Next_Object;
	}
	delete Current_Object;
}
void delete_branch_object(Term*& Current_Trunk_Object, const string& Teacher_Name, const string& Discipline_Name)
{
	// функция удаления объекта ветви
	bool existence = false;
	if (Current_Trunk_Object->Point_to_Branch != nullptr)
	{
		Page* Temporary = Current_Trunk_Object->Point_to_Branch;
		Page* Iterating_Pointer = Current_Trunk_Object->Point_to_Branch;
		while (Iterating_Pointer != nullptr)
		{
			if (Iterating_Pointer->Number != Discipline_Name)
			{
				Temporary = Iterating_Pointer;
				Iterating_Pointer = Iterating_Pointer->Point_to_Next_Object;
			}
			else
			{
				existence = true; break;
			}
		}
		if (existence)
		{
			if (Iterating_Pointer == Current_Trunk_Object->Point_to_Branch)
			{
				Current_Trunk_Object->Point_to_Branch = Iterating_Pointer->Point_to_Next_Object;
			}
			else
			{
				Temporary->Point_to_Next_Object = Iterating_Pointer->Point_to_Next_Object;
			}
			delete Iterating_Pointer;
			display_diagnostic_message(successful_removal_from_the_branch);
		}
		else
		{
			display_diagnostic_message(branch_object_not_found);
		}
	}
	else
	{
		display_diagnostic_message(no_branches_found_associated_with_this_trunk_object);
	}
}
void show_structure()
{
	// функция отображения структуры данных на экране
	int index = 1;
	cout << endl << endl;
	cout << "Current data available:\n\n";
	Term* Temporary_Trunk_Object = Beginning_Pointer;
	while (Temporary_Trunk_Object != nullptr)
	{
		cout << "[" << index++ << "]" << "\t";
		cout << Temporary_Trunk_Object->Name << endl << endl; // вывести фамилию преподавателя
		Page* Temporary_Branch_Object = Temporary_Trunk_Object->Point_to_Branch;
		while (Temporary_Branch_Object != nullptr) // пока указатель в ветви не равен указателю на последний элемент
		{
			cout << "\t-\t";
			cout << Temporary_Branch_Object->Number << endl; // вывести название предмета
			Temporary_Branch_Object = Temporary_Branch_Object->Point_to_Next_Object; //переместить указатель на следующий элемент
		}
		Temporary_Trunk_Object = Temporary_Trunk_Object->Point_to_Next_Object; // переставить указатель к следующему элементу
		cout << endl << endl;
	}
}
int read_from_file(string& filename) //функция сичтывания структуры данных из файла
{
	if (filename.find(".txt") == string::npos)
	{
		filename += ".txt";
	}
	ifstream reading_filestream(filename);
	string voyager;
	getline(reading_filestream, voyager);
	if (reading_filestream.is_open())
	{
		// если первая строка в файле равна строке, указывающей, что данный файл соответствует входному файлу для данной программы
		stringstream torrent;
		while (getline(reading_filestream, voyager))
		{
			if (voyager.size() != false)
			{
				Term Buffer;
				torrent << voyager;
				voyager.clear();
				while (torrent >> voyager) // извлечение строк из строкового потока
				{
					if (Buffer.Name.size() == false)
					{
						Buffer.Name = voyager;
						Add_Term(voyager); // добавить элемент в ствол структуры
					}
					else Add_Page(Buffer.Name, voyager); // добавить элемент в ветвь структуры
				}
				torrent.clear(); voyager.clear();
			}
		}
		reading_filestream.close();
		return true;
	}
	else
	{
		return false;
	}
}
bool check_trunk_availability(Term*& Iterating_Pointer, const string& Name)
{
	// функция проверки наличия преподавателя с заданной фамилией в структуре
	Term Temporary(Name);
	bool existence = false; // показатель наличия
	while (Iterating_Pointer != nullptr) // пока указатель на элемент ствола непустой
	{
		if (Iterating_Pointer->Name == Name) // если совпали имена преподавателей
		{
			existence = true;
			break;
		}
		else
		{
			Iterating_Pointer = Iterating_Pointer->Point_to_Next_Object; // переместить указатель на следующий элемент в стволе структуры
		}
	}
	return existence;
}
void clear_structure() // функция, удаляющая структуру данных
{
	Term* Temporary = Beginning_Pointer;
	Term* Iterator = Temporary;
	while (Iterator != nullptr)
	{
		Temporary = Iterator;
		if (Temporary->Point_to_Branch != nullptr)
		{
			Page* Iterating_Pointer = Temporary->Point_to_Branch;
			Page* temporary;
			while (Iterating_Pointer->Point_to_Next_Object != nullptr)
			{
				temporary = Iterating_Pointer->Point_to_Next_Object;
				delete Iterating_Pointer;
				Iterating_Pointer = temporary;
			}
		}
		Iterator = Temporary->Point_to_Next_Object;
		delete Temporary;
	}
	Beginning_Pointer = nullptr; // указатель на первый элемент становится пустым
}
int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "");
	bool end_of_program = false; // показатель конца работы программы

	do
	{
		show_main_menu(); // вывод главного меню на экран
		switch (_getch()) // считывание клавишы меню
		{
		case '1':// добавить элемент в ствол структуры
		{
			//display_current_operation(add_to_trunk);
			string Term_Name;
			cout << "Enter term: ";
			getline(cin, Term_Name);
			if (Term_Name != "close" && Term_Name.size() != false)
			{
				Add_Term(Term_Name);
				display_diagnostic_message(successful_addition_to_the_trunk);
				clear_screen();
				unsaved_changes = true;
			}
			else
			{
				system("cls");
			}
			break;
		}
		case '2': //добавить элемент в ветвь структуры
		{
			display_current_operation(add_to_branch);
			string Term_Name;
			cout << "Enter teacher's name: ";
			getline(cin, Term_Name);
			if (Term_Name != "close" && Term_Name.size() != false)
			{
				Term* Current_Object = Beginning_Pointer;
				cout << endl << endl;
				if (check_trunk_availability(Current_Object, Term_Name) == true)
				{
					string Page_Number;
					cout << "Enter name of discipline: ";
					getline(cin, Page_Number);
					if (Page_Number.size() != false)
					{
						Add_Page(Term_Name, Page_Number);
						display_diagnostic_message(successful_addition_to_the_branch);
						unsaved_changes = true;
					}
					else
					{
						display_diagnostic_message(empty_data);
					}
				}
				else
				{
					display_diagnostic_message(trunk_object_not_found);
				}
				clear_screen();
			}
			else
			{
				system("cls");
			}
			break;
		}
		case '3': //загрузить структуру из файла
		{
			display_current_operation(read_structure_from_file);

			if (unsaved_changes == true && Beginning_Pointer != nullptr)
			{
				cout << "you have unsaved changes. do you want to save current structure?[y/n]\n";
				switch (_getch())
				{
				case 'y':
				{
					string name_of_file = write_to_file_all();
					display_diagnostic_message(successful_save_to_file);
					cout << "Name of Your file: " << name_of_file << endl << endl;
					cout << "Path to Your file: " << fs::current_path() << endl << endl;
					clear_screen();
					show_main_menu();
					display_current_operation(read_structure_from_file);
					break;
				}
				default: {}
				}
			}
			clear_structure();
			cout << "Enter filename without extension: ";
			string filename;
			getline(cin, filename);
			if (filename != "close")
			{
				if (read_from_file(filename) == true)
				{
					display_diagnostic_message(successful_loading_from_file);
				}
				else
				{
					display_diagnostic_message(incorrect_file);
				}
			}
			clear_screen();
			unsaved_changes = false;
			break;
		}
		case '4': // сохранить структуру в файл
		{
			//display_current_operation(save_structure_to_file);
			if (Beginning_Pointer != nullptr)
			{
				string name_of_file = write_to_file_all();
				display_diagnostic_message(successful_save_to_file);
				cout << "Name of Your file: " << name_of_file << endl << endl;
				cout << "Path to Your file: " << fs::current_path() << endl << endl;
				unsaved_changes = false;
			}
			else
			{
				display_diagnostic_message(empty_structure_while_saving);
			}
			clear_screen();
			break;
		}
		case '5': // удалить объект ствола
		{
			display_current_operation(remove_trunk_object);
			if (Beginning_Pointer != nullptr)
			{
				string Term_Name;
				cout << "Enter term: ";
				getline(cin, Term_Name);
				if (Term_Name != "close")
				{
					Term* Current_Object = Beginning_Pointer;
					if (check_trunk_availability(Current_Object, Term_Name) == true)
					{
						delete_trunk_object(Current_Object, Term_Name);
						display_diagnostic_message(successful_removal_from_the_trunk);
						unsaved_changes = true;
					}
					else
					{
						display_diagnostic_message(trunk_object_not_found);
					}
				}
			}
			else
			{
				display_diagnostic_message(empty_structure_while_erasing);
			}
			clear_screen();
			break;
		}
		case '6': // удалить страницу
		{
			display_current_operation(remove_branch_object);
			if (Beginning_Pointer != nullptr)
			{
				Term* Current_Object = Beginning_Pointer;
				string Term_Name;
				string Page_Number;
				cout << "Enter term: ";
				getline(cin, Term_Name);
				if (Term_Name != "close")
				{
					if (check_trunk_availability(Current_Object, Term_Name) == true)
					{
						cout << "Enter page number to delete: ";
						getline(cin, Page_Number);
						delete_branch_object(Current_Object, Term_Name, Page_Number);
						unsaved_changes = true;
					}
					else
					{
						display_diagnostic_message(trunk_object_not_found);
					}
				}
			}
			else
			{
				display_diagnostic_message(empty_structure_while_erasing);
			}
			clear_screen();
			break;
		}
		case '7': // вывести структуру на экран консоли
		{
			if (Beginning_Pointer != nullptr)
			{
				show_structure();
			}
			else
			{
				display_diagnostic_message(empty_structure_while_displaying);
			}
			clear_screen();
			break;
		}
		case 27: // выход из программы
		{
			if (unsaved_changes == true && Beginning_Pointer != nullptr)
			{
				cout << "you have unsaved changes. do you want to save current structure?[y/n]\n";
				switch (_getch())
				{
				case 'y':
				{
					string name_of_file = write_to_file_all();
					display_diagnostic_message(successful_save_to_file);
					cout << "Name of Your file: " << name_of_file << endl << endl;
					cout << "Path to Your file: " << fs::current_path() << endl << endl;
					clear_structure();
					clear_screen();
					show_main_menu();
					break;
				}
				default: {}
				}
			}
			end_of_program = true;
		}
		default:
		{
			system("cls");
		}
		}

	} while (end_of_program == false);

	if (Beginning_Pointer != nullptr)
	{
		clear_structure(); // очистить память после окончания работы пользователя
	}
	return 0;
}