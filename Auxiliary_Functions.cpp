#include"Auxiliary_Functions.h"
void SetColor(const int& text, const int& background)
{
	// ������� ��������� ����� ������ �� ������
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE); // ���������� ���������� ������������ ������ - ����� ������ ��� ������ ������� � �������
	SetConsoleTextAttribute(hStdOut, static_cast<WORD>((background << 4) | text)); // ����� �������� ��� ����� � ������ �������
}
void clear_screen()
{
	system("pause");
	system("cls");
}
void display_current_operation(const int& number_of_operation)
{
	// ������� ����������� ������� �������� �� ������ �������
	if (number_of_operation != 27)
	{
		cout << "Current operation: ";
		SetColor(orange, 0);
		switch (number_of_operation)
		{
			case add_to_trunk:
			{
				cout << "Add teacher\n\n";
				break;
			}
			case add_to_branch:
			{
				cout << "Add discipline related to the teacher.\n\n";
				break;
			}
			case read_structure_from_file:
			{
				cout << "Load data structure from a file\n\n";
				break;
			}
			case save_structure_to_file:
			{
				cout << "Save data structure to a file.\n\n";
				break;
			}
			case remove_trunk_object:
			{
				cout << "Erase teacher\n\n";
				break;
			}
			case remove_branch_object:
			{
				cout << "Erase discipline related to the teacher\n\n";
				break;
			}
		}
		SetColor(white, 0);
		cout << "To exit write close\n\n";
	}
}
void display_diagnostic_message(const int& number_of_operation)
{
	// ������� ������ ��������������� ���������
	switch (number_of_operation)
	{

		case successful_addition_to_the_trunk:
		{
			SetColor(blue, 0);
			cout << "\n\nThe teacher has been successfully added.\n\n";
			break;
		}
		case successful_addition_to_the_branch:
		{
			SetColor(blue, 0);
			cout  << "\n\nDiscipline has been successfully added.\n\n";
			break;
		}
		case successful_loading_from_file:
		{
			SetColor(blue, 0);
			cout << "\n\nData structure from the file has been successfully loaded.\n\n";
			break;
		}
		case successful_save_to_file:
		{
			SetColor(blue, 0);
			cout << "The file has been successfully saved. Search it in the folder with the program.\n\n";
			break;
		}
		case successful_removal_from_the_trunk:
		{
			SetColor(blue, 0);
			cout << "\n\nTeacher has been deleted.\n\n";
			break;
		}
		case successful_removal_from_the_branch:
		{
			SetColor(blue, 0);
			cout << "\n\nDiscipline has been deleted.\n\n";
			break;
		}
		
		case trunk_object_not_found:
		{
			SetColor(red, 0);
			cout << "\n\nNo such teacher has been found.\n\n";
			break;
		}
		case branch_object_not_found:
		{
			SetColor(red, 0);
			cout << "\n\nNo such discipline has been found.\n\n";
			break;
		}
		case no_branches_found_associated_with_this_trunk_object:
		{
			SetColor(red, 0);
			cout << "\n\nNo disciplines related to this teacher has been found.\n\n";
			break;
		}
		case empty_data:
		{
			SetColor(red, 0);
			cout << "\n\nNo data has been entered.\n\n";
			break;
		}
		case incorrect_file:
		{
			SetColor(red, 0);
			cout << "\n\nFile is not suitable for this program or does not exist.\n\n";
			break;
		}
		case empty_structure_while_saving:
		{
			SetColor(red, 0);
			cout << "\n\nData structure is empty. There is nothing to write to the file.\n\n";
			break;
		}
		case empty_structure_while_erasing:
		{
			SetColor(red, 0);
			cout << "\n\nData structure is empty. There is nothing to erase.\n\n";
			break;
		}
		case empty_structure_while_displaying:
		{
			SetColor(red, 0);
			cout << "\n\nData structure is empty. There is nothing to show.\n\n";
			break;
		}
	}
	SetColor(white, 0);
}
void clear_substring_from_punctuation_marks(string& str) // ������� ������� ������ �� ������ ����������
{
	ifstream reading_filestream("Punctuation_Symbols.txt"); // �������� ����� �� ������� ����������
	string file_iterator; // �������� ������
	getline(reading_filestream, file_iterator); // ������� ������, ��������� �� ������ ����������, �� �����
	size_t position = 0;
	for (int i = 0; i < file_iterator.size(); i++) // �������� �� ������
	{
		do
		{
			position = str.find(file_iterator[i]); // ����� � ������ ����� ����������
			if (position != string::npos) // ���� ������ ���� ����������
			{
				str.erase(position, 1); // ������� ���
			}
		} while (position != string::npos);
		position = 0;
	}
	reading_filestream.close();
}
void show_main_menu() // ������� ������ �������� ���� �� ����� ������������
{
	cout << "����� ������� ����� ����, ������� ������ ��������������� ������.\n\n";
	cout << "[1] - �������� ������ � ���������\n";
	cout << "[2] - �������� ��������, �� ������� ����������� ������\n";
	cout << "[3] - ��������� ���������� ��������� �� �����\n";
	cout << "[4] - �������� � ���� ���������� ���������\n";
	cout << "[5] - ������� ������\n";
	cout << "[6] - ������� ��������, �� ������� ����������� ������\n";
	cout << "[7] - �������� ���������� ���������\n";
	cout << "[ESC] - ������� ���������\n";
	cout << endl << endl;
}