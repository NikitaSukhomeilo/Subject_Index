#pragma once
#include<iostream>
#include<string>
#include<conio.h>
#include<fstream>
#include<sstream>
#include<windows.h>
#include<chrono>
using namespace std;
enum ConsoleColors
{
	blue = 3,
	red = 4,
	orange = 6,
	white = 7
};
enum DiagnosticMessages
{
	successful_addition_to_the_trunk = 1,
	successful_addition_to_the_branch = 2,
	successful_loading_from_file = 3,
	successful_save_to_file = 4,
	successful_removal_from_the_trunk = 5,
	successful_removal_from_the_branch = 6,
	trunk_object_not_found = 200,
	branch_object_not_found = 201,
	no_branches_found_associated_with_this_trunk_object = 202,
	empty_data = 203,
	incorrect_file = 204,
	empty_structure_while_saving = 205,
	empty_structure_while_erasing = 206,
	empty_structure_while_displaying = 207
};
enum CurrentOperations
{
	add_to_trunk = 1,
	add_to_branch = 2,
	read_structure_from_file = 3,
	save_structure_to_file = 4,
	remove_trunk_object = 5,
	remove_branch_object = 6
};
void SetColor(const int&, const int&); // функция установки цвета шрифта на экране
void clear_screen();
void display_current_operation(const int&); // функция отображения текущей операции на экране консоли
void display_diagnostic_message(const int&); // функция вывода диагностических сообщений
void show_main_menu(); // функция вывода главного меню на экран пользователя
