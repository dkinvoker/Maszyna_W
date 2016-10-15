#pragma once
#include <iostream>
#include <string>
#include <fstream>

namespace Compilator_WJMW 
{

	using namespace std;
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^  TextBox_Pole_edytora;
	protected:

	private: System::Windows::Forms::Panel^  panel1;
	private: System::Windows::Forms::Button^  Button_kompiluj;
	private: System::Windows::Forms::Label^  Label_Iloœæ_Liter;



	protected:

	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->TextBox_Pole_edytora = (gcnew System::Windows::Forms::TextBox());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->Label_Iloœæ_Liter = (gcnew System::Windows::Forms::Label());
			this->Button_kompiluj = (gcnew System::Windows::Forms::Button());
			this->panel1->SuspendLayout();
			this->SuspendLayout();
			// 
			// TextBox_Pole_edytora
			// 
			this->TextBox_Pole_edytora->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(238)));
			this->TextBox_Pole_edytora->Location = System::Drawing::Point(3, 45);
			this->TextBox_Pole_edytora->MaximumSize = System::Drawing::Size(300, 1000);
			this->TextBox_Pole_edytora->MinimumSize = System::Drawing::Size(1136, 400);
			this->TextBox_Pole_edytora->Multiline = true;
			this->TextBox_Pole_edytora->Name = L"TextBox_Pole_edytora";
			this->TextBox_Pole_edytora->Size = System::Drawing::Size(1136, 400);
			this->TextBox_Pole_edytora->TabIndex = 0;
			this->TextBox_Pole_edytora->TextChanged += gcnew System::EventHandler(this, &MyForm::textBox1_TextChanged);
			// 
			// panel1
			// 
			this->panel1->Controls->Add(this->Label_Iloœæ_Liter);
			this->panel1->Controls->Add(this->Button_kompiluj);
			this->panel1->Controls->Add(this->TextBox_Pole_edytora);
			this->panel1->Location = System::Drawing::Point(12, 12);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(1144, 530);
			this->panel1->TabIndex = 1;
			// 
			// Label_Iloœæ_Liter
			// 
			this->Label_Iloœæ_Liter->AutoSize = true;
			this->Label_Iloœæ_Liter->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(238)));
			this->Label_Iloœæ_Liter->Location = System::Drawing::Point(3, 448);
			this->Label_Iloœæ_Liter->Name = L"Label_Iloœæ_Liter";
			this->Label_Iloœæ_Liter->Size = System::Drawing::Size(108, 24);
			this->Label_Iloœæ_Liter->TabIndex = 2;
			this->Label_Iloœæ_Liter->Text = L"Iloœæ Liter: 0";
			// 
			// Button_kompiluj
			// 
			this->Button_kompiluj->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(238)));
			this->Button_kompiluj->Location = System::Drawing::Point(5, 3);
			this->Button_kompiluj->Name = L"Button_kompiluj";
			this->Button_kompiluj->Size = System::Drawing::Size(129, 36);
			this->Button_kompiluj->TabIndex = 1;
			this->Button_kompiluj->Text = L"Kompiluj";
			this->Button_kompiluj->UseVisualStyleBackColor = true;
			this->Button_kompiluj->Click += gcnew System::EventHandler(this, &MyForm::Button_kompiluj_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1168, 554);
			this->Controls->Add(this->panel1);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void textBox1_TextChanged(System::Object^  sender, System::EventArgs^  e) 
	{
		unsigned long long int Iloœæ_liter = 0;
		for (unsigned long long int i = 0; i < TextBox_Pole_edytora->Text->Length; i++)
		{
			if (!Char::IsWhiteSpace(TextBox_Pole_edytora->Text[i]))
			{
				Iloœæ_liter++;
			}

		}
		Label_Iloœæ_Liter->Text = "Iloœæ Liter: " + Iloœæ_liter.ToString();
	}
	private: System::Void Button_kompiluj_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		String^ TextBuffer;
		for (unsigned long long int i = 0; i < TextBox_Pole_edytora->TextLength; i ++)
		{
			TextBuffer += TextBox_Pole_edytora->Text[i];
		}
	}
};
}
