#include "MainScreen.h"
using namespace System;
using namespace System::Windows::Forms; // пространство имён, предоставляющее доступ к функциям работы с окнами
using namespace std;
using namespace msclr::interop;
[STAThreadAttribute] // обязательное требование для обмена сообщениями с сервером сообщений Windows с компонентами COM - системные диалоги
int main(cli::array<String^>^ arguments)
{
	Application::EnableVisualStyles(); // включает визуальные стили для приложения
	Application::SetCompatibleTextRenderingDefault(false); // задаёт по умолчанию значения для свойств определённых компонентов управления
	UIVersion::MainScreen Page; // переименовать пространство имен
	Application::Run(% Page); // запуск приложения
	return 0;
}
String^ UIVersion::MainScreen::get_current_directory() // получение текущей папки с программой
{
	char buffer[MAX_PATH];
	GetCurrentDirectoryA(256, buffer);
	string x = string(buffer) + "\\";
	return marshal_as<String^>(x);// преобразование типов строк
}
void UIVersion::MainScreen::show_structure() // отображение структуры на экране
{
	string buffer;
	Term* Temporary_Trunk_Object = Beginning_Pointer;
	while (Temporary_Trunk_Object != 0)
	{
		buffer = Temporary_Trunk_Object->Name + "  ";// вывести Термин
		Page* Temporary_Branch_Object = Temporary_Trunk_Object->Point_to_Branch;
		while (Temporary_Branch_Object != 0) // пока указатель в ветви не равен указателю на последний элемент
		{
			buffer += " " + Temporary_Branch_Object->Number; // вывести страницу
			Temporary_Branch_Object = Temporary_Branch_Object->Point_to_Next_Object; //переместить указатель на следующий элемент
		}
		UIVersion::MainScreen::Screen->Items->Add(marshal_as<String^>(buffer.c_str()));
		Temporary_Trunk_Object = Temporary_Trunk_Object->Point_to_Next_Object; // переставить указатель к следующему элементу
		buffer.clear();
	}
}
void UIVersion::MainScreen::update_screen() // обновление экрана просмотра после изменений в структуре
{
	this->Screen->Items->Clear(); // очистить весь экран просмотра
	show_structure(); // вывести все элементы структуры
}
System::Void UIVersion::MainScreen::открытьToolStripMenuItem_Click_1(System::Object^ sender, System::EventArgs^ e)
{
	if (EmptyStructureLabel->Visible == true)
	{
		EmptyStructureLabel->Visible = false;
	}
	if (WrongFileLabel->Visible == true)
	{
		WrongFileLabel->Visible = false;
	}
	if (AddTerm->Enabled == false)
	{
		AddTerm->Enabled = true;
	}
	// выбрать файл и  загрузить структуру
	Stream^ stream;
	OpenFileDialog^ Select_File = gcnew OpenFileDialog(); // открыть диалоговое окно для выбора исходного файла
	Select_File->InitialDirectory = get_current_directory(); // установить первоначальное место открытия окна для сохранения файла в папке с программой
	Select_File->Filter = "txt files (*.txt)|*.txt";  // выбор только текстовых файлов
	this->DialogResult = Select_File->ShowDialog();
	if (this->DialogResult == System::Windows::Forms::DialogResult::OK)
	{
		// обработки кнопки ок при выборе файла в проводнике
		if ((stream = Select_File->OpenFile())) // если файл открывается
		{
			*inbound_filename = marshal_as<string>(Select_File->FileName); // привести к строковому типу std::string название входного файла для передачи в сортировку 
			stream->Close();
		}
		if (read_from_file(*inbound_filename) == false)
		{
			WrongFileLabel->Visible = true;
			AddTerm->Enabled = false;
		}
		else
		{
			unsaved_changes = true;
			update_screen();
		}
	}
	if (this->DialogResult == System::Windows::Forms::DialogResult::Cancel)
	{
		// обработка кнопки выход при выборе файла в проводнике
	}
	delete Select_File;
}

System::Void UIVersion::MainScreen::сохранитьКакToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (Screen->Items->Count == false)
	{
		EmptyStructureLabel->Visible = true;
	}
	else
	{
		Stream^ stream;
		SaveFileDialog^ Select_File = gcnew SaveFileDialog(); // объявление и инициализация диалога открытия проводника
		Select_File->InitialDirectory = get_current_directory(); // установить первоначальное место открытия окна для сохранения файла в папке с программой
		Select_File->Filter = "txt files (*.txt)|*.txt";  // выбор только текстовых файлов
		this->DialogResult = Select_File->ShowDialog();
		if (this->DialogResult == System::Windows::Forms::DialogResult::OK)
		{
			// обработки кнопки ок при выборе файла в проводнике
			if ((stream = Select_File->OpenFile())) // если файл открывается
			{
				*outbound_filename = marshal_as<string>(Select_File->FileName); // привести к строковому типу std::string название входного файла для передачи в сортировку 
				stream->Close(); // закрытие диалога проводника
				write_to_file(*outbound_filename);
			}
		}
		if (this->DialogResult == System::Windows::Forms::DialogResult::Cancel)
		{
			// обработка кнопки выход при выборе файла в проводнике
		}
		delete Select_File;
		unsaved_changes = false;
	}
}
System::Void UIVersion::MainScreen::DeleteTerm_Click(System::Object^ sender, System::EventArgs^ e)
{
	string selected_term = marshal_as<string>(Screen->SelectedItem->ToString());
	size_t position = 0;
	// извлечь название термина
	selected_term = selected_term.substr(0, (selected_term.find("  ")));
	Term* Current_Object = Beginning_Pointer;
	if (check_trunk_availability(Current_Object, selected_term) == true)
	{
		delete_trunk_object(Current_Object);
		unsaved_changes = true;
		update_screen();
		if (this->Screen->Items->Count == 0)
		{
			DeleteTerm->Enabled = false;
		}
	}
}
System::Void UIVersion::MainScreen::выйтиToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	UIVersion::clear_structure();
	UIVersion::MainScreen::~MainScreen();
}
System::Void UIVersion::MainScreen::новыйToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (EmptyStructureLabel->Visible == true)
	{
		EmptyStructureLabel->Visible = false;
	}
	if (WrongFileLabel->Visible == true)
	{
		WrongFileLabel->Visible = false;
	}
	if (AddTerm->Enabled == false)
	{
		AddTerm->Enabled = true;
	}
	clear_structure();
	this->Screen->Items->Clear();
	*inbound_filename = "";
	*outbound_filename = "";
}
System::Void UIVersion::MainScreen::сохранитьToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (Screen->Items->Count == false)
	{
		EmptyStructureLabel->Visible = true;
	}
	if (unsaved_changes == true)
	{
		if (*outbound_filename != "")
		{
			write_to_file(*outbound_filename);
		}
		else
		{
			Stream^ stream;
			SaveFileDialog^ Select_File = gcnew SaveFileDialog(); // объявление и инициализация диалога открытия проводника
			Select_File->InitialDirectory = get_current_directory(); // установить первоначальное место открытия окна для сохранения файла в папке с программой
			Select_File->Filter = "txt files (*.txt)|*.txt";  // выбор только текстовых файлов
			this->DialogResult = Select_File->ShowDialog();
			if (this->DialogResult == System::Windows::Forms::DialogResult::OK)
			{
				// обработки кнопки ок при выборе файла в проводнике
				if ((stream = Select_File->OpenFile())) // если файл открывается
				{
					*outbound_filename = marshal_as<string>(Select_File->FileName); // привести к строковому типу std::string название входного файла для передачи в сортировку 
					stream->Close(); // закрытие диалога проводника
					write_to_file(*outbound_filename);
				}
			}
			if (this->DialogResult == System::Windows::Forms::DialogResult::Cancel)
			{
				// обработка кнопки выход при выборе файла в проводнике
			}
			delete Select_File;
		}
		unsaved_changes = false;
	}
}
System::Void UIVersion::MainScreen::AddTerm_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (EmptyStructureLabel->Visible == true)
	{
		EmptyStructureLabel->Visible = false;
	}
	this->ApplyChanges->Show();
	this->EnterPage->Show();
	this->EnterPageLabel->Show();
	this->EnterTerm->Show();
	this->EnterTermLabel->Show();
}
System::Void UIVersion::MainScreen::ApplyChanges_Click(System::Object^ sender, System::EventArgs^ e)
{
	string record = marshal_as<string>(this->EnterTerm->Text);
	string page;
	bool correct = true;
	DiagMes_1->Hide();
	if (EnterPage->Text != "")
	{
		page = marshal_as<string>(this->EnterPage->Text);
		for (const auto& iterator : page)
		{
			try
			{
				if (iterator != ',' && iterator != ' ')
				{
					if (!isdigit(iterator) && isalpha(iterator))
					{
						DiagMes_1->Show();
						correct = false;
						break;
					}
				}
			}
			catch (exception& error)
			{
				DiagMes_1->Show();
				correct = false;
				break;
			}
		}
	}
	if (correct)
	{
		string prev;
		if (this->Screen->Items->Count != 0)
		{
			prev = marshal_as<string>(this->Screen->SelectedItem->ToString());
			prev = prev.substr(0, (prev.find(' '))); // извлечь из строки название выбранного термина
			Term* Current_Object = new Term(record);
			string page_number;
			for (size_t i = 0; i < page.size(); i++)
			{
				char Iterator = page[i];
				if (i == (page.size() - 1))
				{
					page_number += Iterator;
					Page* New_Object = new Page(page_number);// инициализация его полей
					if (Current_Object->Point_to_Branch != 0) // если в ветви есть объекты
					{
						Page* Iterating_Pointer = Current_Object->Point_to_Branch;
						while (Iterating_Pointer->Point_to_Next_Object != 0) // пока указатель на объект ветви непустой
						{
							Iterating_Pointer = Iterating_Pointer->Point_to_Next_Object; // переставить указатель ветви на следующий элемент
						}
						Iterating_Pointer->Point_to_Next_Object = New_Object;// указатель на ветвь объекта ствола равен указателю на новый объект 
					}
					else
					{
						Current_Object->Point_to_Branch = New_Object; // указатель на ветвь объекта ствола равен указателю на новый объект 
						New_Object->Point_to_Next_Object = 0; // указатель на следующий объект ветви равен пустому указателю
					}
					page_number.clear();
				}
				else if (Iterator != ' ' && Iterator != ',')
				{
					page_number += Iterator;
				}
				else if ((page_number.size()) && (Iterator == ' ' || Iterator == ','))
				{
					Page* New_Object = new Page(page_number);// инициализация его полей
					if (Current_Object->Point_to_Branch != 0) // если в ветви есть объекты
					{
						Page* Iterating_Pointer = Current_Object->Point_to_Branch;
						while (Iterating_Pointer->Point_to_Next_Object != 0) // пока указатель на объект ветви непустой
						{
							Iterating_Pointer = Iterating_Pointer->Point_to_Next_Object; // переставить указатель ветви на следующий элемент
						}
						Iterating_Pointer->Point_to_Next_Object = New_Object;// указатель на ветвь объекта ствола равен указателю на новый объект 
					}
					else
					{
						Current_Object->Point_to_Branch = New_Object; // указатель на ветвь объекта ствола равен указателю на новый объект 
						New_Object->Point_to_Next_Object = 0; // указатель на следующий объект ветви равен пустому указателю
					}
					page_number.clear();
				}
			}

			Term* Iterator = Beginning_Pointer;

			if (prev != Beginning_Pointer->Name)
			{
				while (Iterator->Name != prev)
				{
					Iterator = Iterator->Point_to_Next_Object;
				}
			}

			Current_Object->Point_to_Next_Object = Iterator->Point_to_Next_Object;
			Iterator->Point_to_Next_Object = Current_Object;
		}
		else
		{
			Term* Current_Object = new Term(record);
			string page_number;
			for (size_t i = 0; i< page.size(); i++)
			{
				char iterator = page[i];
				if (i == (page.size() - 1))
				{
					page_number += iterator;
					Page* New_Object = new Page(page_number);// инициализация его полей
					if (Current_Object->Point_to_Branch != 0) // если в ветви есть объекты
					{
						Page* Iterating_Pointer = Current_Object->Point_to_Branch;
						while (Iterating_Pointer->Point_to_Next_Object != 0) // пока указатель на объект ветви непустой
						{
							Iterating_Pointer = Iterating_Pointer->Point_to_Next_Object; // переставить указатель ветви на следующий элемент
						}
						Iterating_Pointer->Point_to_Next_Object = New_Object;// указатель на ветвь объекта ствола равен указателю на новый объект 
					}
					else
					{
						Current_Object->Point_to_Branch = New_Object; // указатель на ветвь объекта ствола равен указателю на новый объект 
						New_Object->Point_to_Next_Object = 0; // указатель на следующий объект ветви равен пустому указателю
					}
					page_number.clear();
				}
				else if (iterator != ' ' && iterator != ',')
				{
					page_number += iterator;
				}
				else if ((page_number.size()) && (iterator == ' ' || iterator == ','))
				{
					Page* New_Object = new Page(page_number);// инициализация его полей
					if (Current_Object->Point_to_Branch != 0) // если в ветви есть объекты
					{
						Page* Iterating_Pointer = Current_Object->Point_to_Branch;
						while (Iterating_Pointer->Point_to_Next_Object != 0) // пока указатель на объект ветви непустой
						{
							Iterating_Pointer = Iterating_Pointer->Point_to_Next_Object; // переставить указатель ветви на следующий элемент
						}
						Iterating_Pointer->Point_to_Next_Object = New_Object;// указатель на ветвь объекта ствола равен указателю на новый объект 
					}
					else
					{
						Current_Object->Point_to_Branch = New_Object; // указатель на ветвь объекта ствола равен указателю на новый объект 
						New_Object->Point_to_Next_Object = 0; // указатель на следующий объект ветви равен пустому указателю
					}
					page_number.clear();
				}
			}
			Beginning_Pointer = Current_Object;
		}
		this->ApplyChanges->Hide();
		this->EnterPage->Hide(); this->EnterPage->Text = "";
		this->EnterPageLabel->Hide();
		this->EnterTerm->Hide(); this->EnterTerm->Text = "";
		this->EnterTermLabel->Hide();
		update_screen();
		AddTerm->Enabled = false;
		DeleteTerm->Enabled = false;
	}
}
System::Void UIVersion::MainScreen::Screen_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e)
{
	AddTerm->Enabled = true;
	DeleteTerm->Enabled = true;
}
void UIVersion::Add_Term(const string& str) // функция добавления элемента в ствол структуры
{
	Term* Current_Trunk_Object; // указатель на текущий добавляемый объект
	Current_Trunk_Object = new Term(str); // инициализация его полей
	if (Beginning_Pointer != 0) // если структура данных непустая
	{
		Term* Iterating_Pointer = Beginning_Pointer; // указатель для последовательного просмотра структуры для поиска её конца для добавления объекта
		while (Iterating_Pointer->Point_to_Next_Object != 0) // пока указатель на следующий элемент указателя для последовательного просмотра структуры не равен значению пустого указателя
		{
			Iterating_Pointer = Iterating_Pointer->Point_to_Next_Object; // указатель для последовательного просмотра равен указателю на следующий элемент
		}
		Iterating_Pointer->Point_to_Next_Object = Current_Trunk_Object;// указатель на следующий объект в структуре данных теперь указывает на добавленный объект
	}
	else Beginning_Pointer = Current_Trunk_Object; // указатель на первый объект в структуре данных теперь указывает на добавленный объект
}
void UIVersion::Add_Page(const string& Name_of_Term, const string& Number_of_Page) // функция добавления элемента в ветвь структуры
{
	Term* Current_Trunk_Object; // указатель на текущий добавляемый объект
	Page* New_Object = new Page(Number_of_Page);// инициализация его полей
	Current_Trunk_Object = Beginning_Pointer;
	while (Current_Trunk_Object->Name != Name_of_Term) // пока значение текущего элемента ствола не равно значению введенной строки
	{
		Current_Trunk_Object = Current_Trunk_Object->Point_to_Next_Object; // переставить указатель ствола на следующий элемент
	}
	if (Current_Trunk_Object->Point_to_Branch != 0) // если в ветви есть объекты
	{
		Page* Iterating_Pointer = Current_Trunk_Object->Point_to_Branch;
		while (Iterating_Pointer->Point_to_Next_Object != 0) // пока указатель на объект ветви непустой
		{
			Iterating_Pointer = Iterating_Pointer->Point_to_Next_Object; // переставить указатель ветви на следующий элемент
		}
		Iterating_Pointer->Point_to_Next_Object = New_Object;// указатель на ветвь объекта ствола равен указателю на новый объект 
	}
	else
	{
		Current_Trunk_Object->Point_to_Branch = New_Object; // указатель на ветвь объекта ствола равен указателю на новый объект 
		New_Object->Point_to_Next_Object = 0; // указатель на следующий объект ветви равен пустому указателю
	}
}
void UIVersion::write_to_file(const string& outbound_filename) // функция записи структуры в файл
{
	ofstream writing_filestream(outbound_filename); // открыть файловый поток на запись 
	Term* Trunk_Current_Object = Beginning_Pointer;
	do
	{
		writing_filestream << Trunk_Current_Object->Name << '\t';
		if (Trunk_Current_Object->Point_to_Branch != 0)
		{
			Page* Branch_Current_Object = Trunk_Current_Object->Point_to_Branch;
			while (Branch_Current_Object != 0)
			{
				writing_filestream << Branch_Current_Object->Number << ", ";
				Branch_Current_Object = Branch_Current_Object->Point_to_Next_Object;
			}
		}
		Trunk_Current_Object = Trunk_Current_Object->Point_to_Next_Object;
		writing_filestream << endl << endl;
	} while (Trunk_Current_Object != 0);
	writing_filestream.close();
}
void UIVersion::delete_trunk_object(Term*& Current_Object)
{
	// функция удаления объекта ствола 
	Term* TermIterator = Beginning_Pointer; // инициализация текущего элемента самым первым элементом в списке
	if (Current_Object != Beginning_Pointer) // если выбран элемент не в самом начале списка
	{
		// пока указатель на следующий элемент не равен указателю на удаляемый элемент
		while (TermIterator->Point_to_Next_Object != Current_Object) 
		{
			// текущий элемент берется из указателя на следующий элемент
			TermIterator = TermIterator->Point_to_Next_Object;
		}
		TermIterator->Point_to_Next_Object = Current_Object->Point_to_Next_Object;
	}
	else if (Current_Object == Beginning_Pointer) // если выбранный элемент в начале списка
	{
		// указатель на первый элемент теперь указывает на следующий за удаляемым
		Beginning_Pointer = Current_Object->Point_to_Next_Object;
	}
	if (Current_Object->Point_to_Branch != 0) // удаление всех страниц термина
	{
		Page* Iterating_Pointer = Current_Object->Point_to_Branch;
		Page* temporary;
		while (Iterating_Pointer->Point_to_Next_Object != 0)
		{
			temporary = Iterating_Pointer->Point_to_Next_Object;
			delete Iterating_Pointer;
			Iterating_Pointer = temporary;
		}
	}
	delete Current_Object;
}
void UIVersion::delete_branch_object(Term*& Current_Trunk_Object, const string& Number_of_Page)
{
	// функция удаления объекта ветви
	bool existence = false;
	if (Current_Trunk_Object->Point_to_Branch != 0)
	{
		Page* Temporary = Current_Trunk_Object->Point_to_Branch;
		Page* Iterating_Pointer = Current_Trunk_Object->Point_to_Branch;
		while (Iterating_Pointer != 0)
		{
			if (Iterating_Pointer->Number != Number_of_Page)
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
		}
	}
}
int UIVersion::read_from_file(const string& filename) //функция считывания структуры данных из файла
{
	ifstream test(filename);
	string TestString;
	getline(test, TestString);
	try
	{
		if (isdigit(TestString[TestString.size() - 1]) == false)
		{
			getline(test, TestString);
			if (isdigit(TestString[TestString.size() - 1]) == false)
			{
				test.close();
				return false;
			}
		}
	}
	catch (exception& err)
	{
		test.close();
		return false;
	}
	test.close();


	ifstream reading_filestream(filename);
	string file_iterator;
	if (reading_filestream.is_open())
	{
		stringstream torrent;
		while (getline(reading_filestream, file_iterator))
		{
			if (file_iterator.size() > 5)
			{
				size_t position = 0;
				for (size_t i = 0; i < file_iterator.size() - 1; i++)
				{
					if (file_iterator[i] > 47 && file_iterator[i] < 58)
					{
						if (file_iterator[i + 1] > 47 && file_iterator[i + 1] < 58)
						{
							position = i;
							break;
						}
					}
				}
				Term Buffer;
				Buffer.Name = file_iterator.substr(0, position - 1);
				Add_Term(Buffer.Name); // добавить Термин

				string number_of_page;

				for (size_t i = position; i < file_iterator.size(); i++)
				{
					if (file_iterator[i] == ',')
					{
						Add_Page(Buffer.Name, number_of_page);
						number_of_page.clear();
						continue;
					}
					if (i == file_iterator.size() - 1)
					{
						number_of_page += file_iterator[i];
						Add_Page(Buffer.Name, number_of_page);
						number_of_page.clear();
						continue;
					}
					number_of_page += file_iterator[i];
				}
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
bool UIVersion::check_trunk_availability(Term*& Iterating_Pointer, const string& Name)
{
	// функция проверки наличия термина в структуре
	Term Temporary(Name);
	bool existence = false; // показатель наличия
	while (Iterating_Pointer != 0) // пока указатель на элемент ствола непустой
	{
		if (Iterating_Pointer->Name == Name) // если совпали термины
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
void UIVersion::clear_structure() // функция, удаляющая структуру данных
{
	Term* Temporary = Beginning_Pointer;
	Term* Iterator = Temporary;
	while (Iterator != 0)
	{
		Temporary = Iterator;
		if (Temporary->Point_to_Branch != 0)
		{
			Page* Iterating_Pointer = Temporary->Point_to_Branch;
			Page* temporary;
			while (Iterating_Pointer->Point_to_Next_Object != 0)
			{
				temporary = Iterating_Pointer->Point_to_Next_Object;
				delete Iterating_Pointer;
				Iterating_Pointer = temporary;
			}
		}
		Iterator = Temporary->Point_to_Next_Object;
		delete Temporary;
	}
	Beginning_Pointer = 0; // указатель на первый элемент становится пустым
}