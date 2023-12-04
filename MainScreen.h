#pragma once
#pragma comment(lib, "winmm.lib")
#include<iostream>
#include<fstream>
#include<sstream>
#include<exception>
#include<string>
#include<msclr\marshal_cppstd.h> // библиотека для преобразования строк типа String^ в std::string и обратно
namespace UIVersion
{
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;
	using namespace std;
	using namespace msclr::interop;
	/// <summary>
	/// Сводка для MainScreen
	/// </summary>
	struct Page // структура Страница
	{
		string Number; // численное значение страницы
		Page* Point_to_Next_Object; // указатель на следующий объект в ветви
		Page(const string& str)// инициализирующий конструктор
		{
			Number = str;
			Point_to_Next_Object = 0;
		}
		Page()// конструктор по умолчанию
		{
			Number = "";
			Point_to_Next_Object = 0;
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
			Point_to_Branch = 0;
			Point_to_Next_Object = 0;
		}
		Term() // конструктор по умолчанию
		{
			Name = "";
			Point_to_Branch = 0;
			Point_to_Next_Object = 0;
		}
	};
	void Add_Term(const string&);
	void Add_Page(const string&, const string&);
	void write_to_file_all(const string&);
	void delete_trunk_object(Term*&);
	void delete_branch_object(Term*&, const string&);
	int read_from_file(const string&);
	bool check_trunk_availability(Term*&, const string&);
	void clear_structure();
	Term* Beginning_Pointer;
	bool unsaved_changes;
	Term* Temporary;
	Term* Iterator;
	public ref class MainScreen : public System::Windows::Forms::Form
	{
	public:
		MainScreen(void)
		{
			InitializeComponent();
			inbound_filename = new string{ "" };
			outbound_filename = new string{ "" };
			Beginning_Pointer = 0; // указатель на самый первый объект в структуре
			unsaved_changes = false; // показатель наличия изменений в текущей структуре при работе с ней
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MainScreen()
		{
			if (components)
			{
				delete components;
				delete inbound_filename;
				delete Temporary;
				delete Iterator;
				delete Beginning_Pointer;
				Application::Exit();
			}
		}
	private: System::Windows::Forms::Button^ AddTerm;


	private: System::Windows::Forms::Button^ DeleteTerm;
	private: System::Windows::Forms::MenuStrip^ menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^ файлToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ новыйToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ открытьToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ сохранитьToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ сохранитьКакToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ выйтиToolStripMenuItem;
	private: System::Windows::Forms::Label^ EnterTermLabel;
	private: System::Windows::Forms::RichTextBox^ EnterTerm;
	private: System::Windows::Forms::Label^ EnterPageLabel;
	private: System::Windows::Forms::RichTextBox^ EnterPage;
	private: System::Windows::Forms::Button^ ApplyChanges;
	public: System::Windows::Forms::ListBox^ Screen;
	private:
	string* inbound_filename;
	string* outbound_filename;
	System::Windows::Forms::Label^ DiagMes_1;
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

		#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->AddTerm = (gcnew System::Windows::Forms::Button());
			this->DeleteTerm = (gcnew System::Windows::Forms::Button());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->файлToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->новыйToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->открытьToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->сохранитьToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->сохранитьКакToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->выйтиToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->EnterTermLabel = (gcnew System::Windows::Forms::Label());
			this->EnterTerm = (gcnew System::Windows::Forms::RichTextBox());
			this->EnterPageLabel = (gcnew System::Windows::Forms::Label());
			this->EnterPage = (gcnew System::Windows::Forms::RichTextBox());
			this->ApplyChanges = (gcnew System::Windows::Forms::Button());
			this->Screen = (gcnew System::Windows::Forms::ListBox());
			this->DiagMes_1 = (gcnew System::Windows::Forms::Label());
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// AddTerm
			// 
			this->AddTerm->Location = System::Drawing::Point(558, 102);
			this->AddTerm->Name = L"AddTerm";
			this->AddTerm->Size = System::Drawing::Size(115, 48);
			this->AddTerm->TabIndex = 0;
			this->AddTerm->Text = L"Добавить";
			this->AddTerm->UseVisualStyleBackColor = true;
			this->AddTerm->Click += gcnew System::EventHandler(this, &MainScreen::AddTerm_Click);
			// 
			// DeleteTerm
			// 
			this->DeleteTerm->Enabled = false;
			this->DeleteTerm->Location = System::Drawing::Point(558, 210);
			this->DeleteTerm->Name = L"DeleteTerm";
			this->DeleteTerm->Size = System::Drawing::Size(115, 48);
			this->DeleteTerm->TabIndex = 2;
			this->DeleteTerm->Text = L"Удалить";
			this->DeleteTerm->UseVisualStyleBackColor = true;
			this->DeleteTerm->Click += gcnew System::EventHandler(this, &MainScreen::DeleteTerm_Click);
			// 
			// menuStrip1
			// 
			this->menuStrip1->ImageScalingSize = System::Drawing::Size(20, 20);
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->файлToolStripMenuItem });
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(1006, 28);
			this->menuStrip1->TabIndex = 5;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// файлToolStripMenuItem
			// 
			this->файлToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {
				this->новыйToolStripMenuItem,
					this->открытьToolStripMenuItem, this->сохранитьToolStripMenuItem, this->сохранитьКакToolStripMenuItem, this->выйтиToolStripMenuItem
			});
			this->файлToolStripMenuItem->Name = L"файлToolStripMenuItem";
			this->файлToolStripMenuItem->Size = System::Drawing::Size(59, 24);
			this->файлToolStripMenuItem->Text = L"Файл";
			// 
			// новыйToolStripMenuItem
			// 
			this->новыйToolStripMenuItem->Name = L"новыйToolStripMenuItem";
			this->новыйToolStripMenuItem->Size = System::Drawing::Size(192, 26);
			this->новыйToolStripMenuItem->Text = L"Новый";
			this->новыйToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainScreen::новыйToolStripMenuItem_Click);
			// 
			// открытьToolStripMenuItem
			// 
			this->открытьToolStripMenuItem->Name = L"открытьToolStripMenuItem";
			this->открытьToolStripMenuItem->Size = System::Drawing::Size(192, 26);
			this->открытьToolStripMenuItem->Text = L"Открыть";
			this->открытьToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainScreen::открытьToolStripMenuItem_Click_1);
			// 
			// сохранитьToolStripMenuItem
			// 
			this->сохранитьToolStripMenuItem->Name = L"сохранитьToolStripMenuItem";
			this->сохранитьToolStripMenuItem->Size = System::Drawing::Size(192, 26);
			this->сохранитьToolStripMenuItem->Text = L"Сохранить";
			this->сохранитьToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainScreen::сохранитьToolStripMenuItem_Click);
			// 
			// сохранитьКакToolStripMenuItem
			// 
			this->сохранитьКакToolStripMenuItem->Name = L"сохранитьКакToolStripMenuItem";
			this->сохранитьКакToolStripMenuItem->Size = System::Drawing::Size(192, 26);
			this->сохранитьКакToolStripMenuItem->Text = L"Сохранить как";
			this->сохранитьКакToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainScreen::сохранитьКакToolStripMenuItem_Click);
			// 
			// выйтиToolStripMenuItem
			// 
			this->выйтиToolStripMenuItem->Name = L"выйтиToolStripMenuItem";
			this->выйтиToolStripMenuItem->Size = System::Drawing::Size(192, 26);
			this->выйтиToolStripMenuItem->Text = L"Выйти";
			this->выйтиToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainScreen::выйтиToolStripMenuItem_Click);
			// 
			// EnterTermLabel
			// 
			this->EnterTermLabel->AutoSize = true;
			this->EnterTermLabel->Location = System::Drawing::Point(25, 316);
			this->EnterTermLabel->Name = L"EnterTermLabel";
			this->EnterTermLabel->Size = System::Drawing::Size(132, 16);
			this->EnterTermLabel->TabIndex = 6;
			this->EnterTermLabel->Text = L"Название термина";
			this->EnterTermLabel->Visible = false;
			// 
			// EnterTerm
			// 
			this->EnterTerm->Location = System::Drawing::Point(28, 335);
			this->EnterTerm->Name = L"EnterTerm";
			this->EnterTerm->Size = System::Drawing::Size(248, 31);
			this->EnterTerm->TabIndex = 7;
			this->EnterTerm->Text = L"";
			this->EnterTerm->Visible = false;
			// 
			// EnterPageLabel
			// 
			this->EnterPageLabel->AutoSize = true;
			this->EnterPageLabel->Location = System::Drawing::Point(25, 384);
			this->EnterPageLabel->Name = L"EnterPageLabel";
			this->EnterPageLabel->Size = System::Drawing::Size(72, 16);
			this->EnterPageLabel->TabIndex = 8;
			this->EnterPageLabel->Text = L"Страницы";
			this->EnterPageLabel->Visible = false;
			// 
			// EnterPage
			// 
			this->EnterPage->Location = System::Drawing::Point(28, 403);
			this->EnterPage->Name = L"EnterPage";
			this->EnterPage->Size = System::Drawing::Size(248, 31);
			this->EnterPage->TabIndex = 9;
			this->EnterPage->Text = L"";
			this->EnterPage->Visible = false;
			// 
			// ApplyChanges
			// 
			this->ApplyChanges->Location = System::Drawing::Point(28, 453);
			this->ApplyChanges->Name = L"ApplyChanges";
			this->ApplyChanges->Size = System::Drawing::Size(75, 23);
			this->ApplyChanges->TabIndex = 10;
			this->ApplyChanges->Text = L"Готово";
			this->ApplyChanges->UseVisualStyleBackColor = true;
			this->ApplyChanges->Visible = false;
			this->ApplyChanges->Click += gcnew System::EventHandler(this, &MainScreen::ApplyChanges_Click);
			// 
			// Screen
			// 
			this->Screen->FormattingEnabled = true;
			this->Screen->ItemHeight = 16;
			this->Screen->Location = System::Drawing::Point(28, 86);
			this->Screen->Name = L"Screen";
			this->Screen->Size = System::Drawing::Size(515, 196);
			this->Screen->TabIndex = 11;
			this->Screen->SelectedIndexChanged += gcnew System::EventHandler(this, &MainScreen::Screen_SelectedIndexChanged);
			// 
			// DiagMes_1
			// 
			this->DiagMes_1->AutoSize = true;
			this->DiagMes_1->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->DiagMes_1->Location = System::Drawing::Point(297, 406);
			this->DiagMes_1->Name = L"DiagMes_1";
			this->DiagMes_1->Size = System::Drawing::Size(169, 16);
			this->DiagMes_1->TabIndex = 12;
			this->DiagMes_1->Text = L"неверный формат ввода";
			this->DiagMes_1->Visible = false;
			// 
			// MainScreen
			// 
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			this->BackColor = System::Drawing::SystemColors::Control;
			this->ClientSize = System::Drawing::Size(1006, 721);
			this->Controls->Add(this->DiagMes_1);
			this->Controls->Add(this->Screen);
			this->Controls->Add(this->ApplyChanges);
			this->Controls->Add(this->EnterPage);
			this->Controls->Add(this->EnterPageLabel);
			this->Controls->Add(this->EnterTerm);
			this->Controls->Add(this->EnterTermLabel);
			this->Controls->Add(this->DeleteTerm);
			this->Controls->Add(this->AddTerm);
			this->Controls->Add(this->menuStrip1);
			this->MaximizeBox = false;
			this->Name = L"MainScreen";
			this->ShowIcon = false;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Менеджер предметных указателей";
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private:
	String^ get_current_directory();
	void show_structure();
	void update_screen();
	System::Void открытьToolStripMenuItem_Click_1(System::Object^ sender, System::EventArgs^ e);
	System::Void сохранитьКакToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
	System::Void DeleteTerm_Click(System::Object^ sender, System::EventArgs^ e);
	System::Void выйтиToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
	System::Void новыйToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
	System::Void сохранитьToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
	System::Void AddTerm_Click(System::Object^ sender, System::EventArgs^ e);
	System::Void ApplyChanges_Click(System::Object^ sender, System::EventArgs^ e);
    System::Void Screen_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e);
};
}
