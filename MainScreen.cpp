#include "MainScreen.h"
using namespace System;
using namespace System::Windows::Forms; // ������������ ���, ��������������� ������ � �������� ������ � ������
using namespace std;
using namespace msclr::interop;
[STAThreadAttribute] // ������������ ���������� ��� ������ ����������� � �������� ��������� Windows � ������������ COM - ��������� �������
int main(cli::array<String^>^ arguments)
{
	Application::EnableVisualStyles(); // �������� ���������� ����� ��� ����������
	Application::SetCompatibleTextRenderingDefault(false); // ����� �� ��������� �������� ��� ������� ����������� ����������� ����������
	UIVersion::MainScreen Page; // ������������� ������������ ����
	Application::Run(% Page); // ������ ����������
	return 0;
}
String^ UIVersion::MainScreen::get_current_directory()
{
	char buffer[MAX_PATH];
	GetCurrentDirectoryA(256, buffer);
	string x = string(buffer) + "\\";
	return marshal_as<String^>(x);// �������������� ����� �����
}
void UIVersion::MainScreen::show_structure()
{
	string buffer;
	Term* Temporary_Trunk_Object = Beginning_Pointer;
	while (Temporary_Trunk_Object != 0)
	{
		buffer = Temporary_Trunk_Object->Name + "  ";// ������� ������
		Page* Temporary_Branch_Object = Temporary_Trunk_Object->Point_to_Branch;
		while (Temporary_Branch_Object != 0) // ���� ��������� � ����� �� ����� ��������� �� ��������� �������
		{
			buffer += " " + Temporary_Branch_Object->Number; // ������� ��������
			Temporary_Branch_Object = Temporary_Branch_Object->Point_to_Next_Object; //����������� ��������� �� ��������� �������
		}
		UIVersion::MainScreen::Screen->Items->Add(marshal_as<String^>(buffer.c_str()));
		Temporary_Trunk_Object = Temporary_Trunk_Object->Point_to_Next_Object; // ����������� ��������� � ���������� ��������
		buffer.clear();
	}
}
void UIVersion::MainScreen::update_screen()
{
	this->Screen->Items->Clear();
	show_structure();
}
System::Void UIVersion::MainScreen::�������ToolStripMenuItem_Click_1(System::Object^ sender, System::EventArgs^ e)
{
	// ������� ���� �  ��������� ���������
	Stream^ stream;
	OpenFileDialog^ Select_File = gcnew OpenFileDialog(); // ������� ���������� ���� ��� ������ ��������� �����
	Select_File->InitialDirectory = get_current_directory(); // ���������� �������������� ����� �������� ���� ��� ���������� ����� � ����� � ����������
	Select_File->Filter = "txt files (*.txt)|*.txt";  // ����� ������ ��������� ������
	this->DialogResult = Select_File->ShowDialog();
	if (this->DialogResult == System::Windows::Forms::DialogResult::OK)
	{
		// ��������� ������ �� ��� ������ ����� � ����������
		if ((stream = Select_File->OpenFile())) // ���� ���� �����������
		{
			*inbound_filename = marshal_as<string>(Select_File->FileName); // �������� � ���������� ���� std::string �������� �������� ����� ��� �������� � ���������� 
			stream->Close();
		}
		read_from_file(*inbound_filename);
		unsaved_changes = true;
		update_screen();
	}
	if (this->DialogResult == System::Windows::Forms::DialogResult::Cancel)
	{
		// ��������� ������ ����� ��� ������ ����� � ����������
	}
	delete Select_File;
}

System::Void UIVersion::MainScreen::������������ToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	Stream^ stream;
	SaveFileDialog^ Select_File = gcnew SaveFileDialog(); // ���������� � ������������� ������� �������� ����������
	Select_File->InitialDirectory = get_current_directory(); // ���������� �������������� ����� �������� ���� ��� ���������� ����� � ����� � ����������
	Select_File->Filter = "txt files (*.txt)|*.txt";  // ����� ������ ��������� ������
	this->DialogResult = Select_File->ShowDialog();
	if (this->DialogResult == System::Windows::Forms::DialogResult::OK)
	{
		// ��������� ������ �� ��� ������ ����� � ����������
		if ((stream = Select_File->OpenFile())) // ���� ���� �����������
		{
			*outbound_filename = marshal_as<string>(Select_File->FileName); // �������� � ���������� ���� std::string �������� �������� ����� ��� �������� � ���������� 
			stream->Close(); // �������� ������� ����������
			write_to_file(*outbound_filename);
		}
	}
	if (this->DialogResult == System::Windows::Forms::DialogResult::Cancel)
	{
		// ��������� ������ ����� ��� ������ ����� � ����������
	}
	delete Select_File;
	unsaved_changes = false;
}
System::Void UIVersion::MainScreen::DeleteTerm_Click(System::Object^ sender, System::EventArgs^ e)
{
	string selected_term = marshal_as<string>(Screen->SelectedItem->ToString());
	size_t position = 0;
	// ������� �������� �������
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
System::Void UIVersion::MainScreen::�����ToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	UIVersion::clear_structure();
	UIVersion::MainScreen::~MainScreen();
}
System::Void UIVersion::MainScreen::�����ToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	clear_structure();
	this->Screen->Items->Clear();
	*inbound_filename = "";
	*outbound_filename = "";
}
System::Void UIVersion::MainScreen::���������ToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (unsaved_changes == true)
	{
		if (*outbound_filename != "")
		{
			write_to_file(*outbound_filename);
		}
		else
		{
			Stream^ stream;
			SaveFileDialog^ Select_File = gcnew SaveFileDialog(); // ���������� � ������������� ������� �������� ����������
			Select_File->InitialDirectory = get_current_directory(); // ���������� �������������� ����� �������� ���� ��� ���������� ����� � ����� � ����������
			Select_File->Filter = "txt files (*.txt)|*.txt";  // ����� ������ ��������� ������
			this->DialogResult = Select_File->ShowDialog();
			if (this->DialogResult == System::Windows::Forms::DialogResult::OK)
			{
				// ��������� ������ �� ��� ������ ����� � ����������
				if ((stream = Select_File->OpenFile())) // ���� ���� �����������
				{
					*outbound_filename = marshal_as<string>(Select_File->FileName); // �������� � ���������� ���� std::string �������� �������� ����� ��� �������� � ���������� 
					stream->Close(); // �������� ������� ����������
					write_to_file(*outbound_filename);
				}
			}
			if (this->DialogResult == System::Windows::Forms::DialogResult::Cancel)
			{
				// ��������� ������ ����� ��� ������ ����� � ����������
			}
			delete Select_File;
		}
		unsaved_changes = false;
	}
}
System::Void UIVersion::MainScreen::AddTerm_Click(System::Object^ sender, System::EventArgs^ e)
{
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
			prev = prev.substr(0, (prev.find(' '))); // ������� �� ������ �������� ���������� �������
			Term* Current_Object = new Term(record);
			string page_number;
			for (size_t i = 0; i < page.size(); i++)
			{
				char Iterator = page[i];
				if (i == (page.size() - 1))
				{
					page_number += Iterator;
					Page* New_Object = new Page(page_number);// ������������� ��� �����
					if (Current_Object->Point_to_Branch != 0) // ���� � ����� ���� �������
					{
						Page* Iterating_Pointer = Current_Object->Point_to_Branch;
						while (Iterating_Pointer->Point_to_Next_Object != 0) // ���� ��������� �� ������ ����� ��������
						{
							Iterating_Pointer = Iterating_Pointer->Point_to_Next_Object; // ����������� ��������� ����� �� ��������� �������
						}
						Iterating_Pointer->Point_to_Next_Object = New_Object;// ��������� �� ����� ������� ������ ����� ��������� �� ����� ������ 
					}
					else
					{
						Current_Object->Point_to_Branch = New_Object; // ��������� �� ����� ������� ������ ����� ��������� �� ����� ������ 
						New_Object->Point_to_Next_Object = 0; // ��������� �� ��������� ������ ����� ����� ������� ���������
					}
					page_number.clear();
				}
				else if (Iterator != ' ' && Iterator != ',')
				{
					page_number += Iterator;
				}
				else if ((page_number.size()) && (Iterator == ' ' || Iterator == ','))
				{
					Page* New_Object = new Page(page_number);// ������������� ��� �����
					if (Current_Object->Point_to_Branch != 0) // ���� � ����� ���� �������
					{
						Page* Iterating_Pointer = Current_Object->Point_to_Branch;
						while (Iterating_Pointer->Point_to_Next_Object != 0) // ���� ��������� �� ������ ����� ��������
						{
							Iterating_Pointer = Iterating_Pointer->Point_to_Next_Object; // ����������� ��������� ����� �� ��������� �������
						}
						Iterating_Pointer->Point_to_Next_Object = New_Object;// ��������� �� ����� ������� ������ ����� ��������� �� ����� ������ 
					}
					else
					{
						Current_Object->Point_to_Branch = New_Object; // ��������� �� ����� ������� ������ ����� ��������� �� ����� ������ 
						New_Object->Point_to_Next_Object = 0; // ��������� �� ��������� ������ ����� ����� ������� ���������
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
					Page* New_Object = new Page(page_number);// ������������� ��� �����
					if (Current_Object->Point_to_Branch != 0) // ���� � ����� ���� �������
					{
						Page* Iterating_Pointer = Current_Object->Point_to_Branch;
						while (Iterating_Pointer->Point_to_Next_Object != 0) // ���� ��������� �� ������ ����� ��������
						{
							Iterating_Pointer = Iterating_Pointer->Point_to_Next_Object; // ����������� ��������� ����� �� ��������� �������
						}
						Iterating_Pointer->Point_to_Next_Object = New_Object;// ��������� �� ����� ������� ������ ����� ��������� �� ����� ������ 
					}
					else
					{
						Current_Object->Point_to_Branch = New_Object; // ��������� �� ����� ������� ������ ����� ��������� �� ����� ������ 
						New_Object->Point_to_Next_Object = 0; // ��������� �� ��������� ������ ����� ����� ������� ���������
					}
					page_number.clear();
				}
				else if (iterator != ' ' && iterator != ',')
				{
					page_number += iterator;
				}
				else if ((page_number.size()) && (iterator == ' ' || iterator == ','))
				{
					Page* New_Object = new Page(page_number);// ������������� ��� �����
					if (Current_Object->Point_to_Branch != 0) // ���� � ����� ���� �������
					{
						Page* Iterating_Pointer = Current_Object->Point_to_Branch;
						while (Iterating_Pointer->Point_to_Next_Object != 0) // ���� ��������� �� ������ ����� ��������
						{
							Iterating_Pointer = Iterating_Pointer->Point_to_Next_Object; // ����������� ��������� ����� �� ��������� �������
						}
						Iterating_Pointer->Point_to_Next_Object = New_Object;// ��������� �� ����� ������� ������ ����� ��������� �� ����� ������ 
					}
					else
					{
						Current_Object->Point_to_Branch = New_Object; // ��������� �� ����� ������� ������ ����� ��������� �� ����� ������ 
						New_Object->Point_to_Next_Object = 0; // ��������� �� ��������� ������ ����� ����� ������� ���������
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
void UIVersion::Add_Term(const string& str) // ������� ���������� �������� � ����� ���������
{
	Term* Current_Trunk_Object; // ��������� �� ������� ����������� ������
	Current_Trunk_Object = new Term(str); // ������������� ��� �����
	if (Beginning_Pointer != 0) // ���� ��������� ������ ��������
	{
		Term* Iterating_Pointer = Beginning_Pointer; // ��������� ��� ����������������� ��������� ��������� ��� ������ � ����� ��� ���������� �������
		while (Iterating_Pointer->Point_to_Next_Object != 0) // ���� ��������� �� ��������� ������� ��������� ��� ����������������� ��������� ��������� �� ����� �������� ������� ���������
		{
			Iterating_Pointer = Iterating_Pointer->Point_to_Next_Object; // ��������� ��� ����������������� ��������� ����� ��������� �� ��������� �������
		}
		Iterating_Pointer->Point_to_Next_Object = Current_Trunk_Object;// ��������� �� ��������� ������ � ��������� ������ ������ ��������� �� ����������� ������
	}
	else Beginning_Pointer = Current_Trunk_Object; // ��������� �� ������ ������ � ��������� ������ ������ ��������� �� ����������� ������
}
void UIVersion::Add_Page(const string& Name_of_Term, const string& Number_of_Page) // ������� ���������� �������� � ����� ���������
{
	Term* Current_Trunk_Object; // ��������� �� ������� ����������� ������
	Page* New_Object = new Page(Number_of_Page);// ������������� ��� �����
	Current_Trunk_Object = Beginning_Pointer;
	while (Current_Trunk_Object->Name != Name_of_Term) // ���� �������� �������� �������� ������ �� ����� �������� ��������� ������
	{
		Current_Trunk_Object = Current_Trunk_Object->Point_to_Next_Object; // ����������� ��������� ������ �� ��������� �������
	}
	if (Current_Trunk_Object->Point_to_Branch != 0) // ���� � ����� ���� �������
	{
		Page* Iterating_Pointer = Current_Trunk_Object->Point_to_Branch;
		while (Iterating_Pointer->Point_to_Next_Object != 0) // ���� ��������� �� ������ ����� ��������
		{
			Iterating_Pointer = Iterating_Pointer->Point_to_Next_Object; // ����������� ��������� ����� �� ��������� �������
		}
		Iterating_Pointer->Point_to_Next_Object = New_Object;// ��������� �� ����� ������� ������ ����� ��������� �� ����� ������ 
	}
	else
	{
		Current_Trunk_Object->Point_to_Branch = New_Object; // ��������� �� ����� ������� ������ ����� ��������� �� ����� ������ 
		New_Object->Point_to_Next_Object = 0; // ��������� �� ��������� ������ ����� ����� ������� ���������
	}
}
void UIVersion::write_to_file(const string& outbound_filename) // ������� ������ ��������� � ����
{
	ofstream writing_filestream(outbound_filename); // ������� �������� ����� �� ������ 
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
	// ������� �������� ������� ������ 
	Term* TermIterator = Beginning_Pointer; // ������������� �������� �������� ����� ������ ��������� � ������
	if (Current_Object != Beginning_Pointer) // ���� ������ ������� �� � ����� ������ ������
	{
		// ���� ��������� �� ��������� ������� �� ����� ��������� �� ��������� �������
		while (TermIterator->Point_to_Next_Object != Current_Object) 
		{
			// ������� ������� ������� �� ��������� �� ��������� �������
			TermIterator = TermIterator->Point_to_Next_Object;
		}
		TermIterator->Point_to_Next_Object = Current_Object->Point_to_Next_Object;
	}
	else if (Current_Object == Beginning_Pointer) // ���� ��������� ������� � ������ ������
	{
		// ��������� �� ������ ������� ������ ��������� �� ��������� �� ���������
		Beginning_Pointer = Current_Object->Point_to_Next_Object;
	}
	if (Current_Object->Point_to_Branch != 0) // �������� ���� ������� �������
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
	// ������� �������� ������� �����
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
int UIVersion::read_from_file(const string& filename) //������� ���������� ��������� ������ �� �����
{
	ifstream reading_filestream(filename);
	string file_iterator;
	if (reading_filestream.is_open())
	{
		stringstream torrent;
		while (getline(reading_filestream, file_iterator))
		{
			if (file_iterator.size() >= 5)
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
				Add_Term(Buffer.Name); // �������� ������

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
	// ������� �������� ������� ������� � ���������
	Term Temporary(Name);
	bool existence = false; // ���������� �������
	while (Iterating_Pointer != 0) // ���� ��������� �� ������� ������ ��������
	{
		if (Iterating_Pointer->Name == Name) // ���� ������� �������
		{
			existence = true;
			break;
		}
		else
		{
			Iterating_Pointer = Iterating_Pointer->Point_to_Next_Object; // ����������� ��������� �� ��������� ������� � ������ ���������
		}
	}
	return existence;
}
void UIVersion::clear_structure() // �������, ��������� ��������� ������
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
	Beginning_Pointer = 0; // ��������� �� ������ ������� ���������� ������
}