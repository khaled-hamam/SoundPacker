#pragma once
#include "SoundPackingLib.h"
#include <msclr\marshal_cppstd.h>

namespace SoundPacker {

	using namespace System;
	using namespace System::Diagnostics;
	using namespace System::IO;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Home
	/// </summary>
	public ref class Home : public System::Windows::Forms::Form
	{
	public:
		Home(void)
		{
			InitializeComponent();

			// Setting ComboBox Options
			array<Object^>^ algorithms = {
				gcnew String(WORST_FIT_LS.c_str()),
				gcnew String(WORST_FIT_PQ.c_str()),
				gcnew String(WORST_FIT_DEC_LS.c_str()),
				gcnew String(WORST_FIT_DEC_PQ.c_str()),
				gcnew String(FIRST_FIT.c_str()),
				gcnew String(BEST_FIT.c_str()),
				gcnew String(FOLDER_FILLING.c_str()),
				gcnew String(MULTITHREADING.c_str()),
			};
			this->algorithmsComboBox->Items->AddRange(algorithms);
		}

	protected:
		/// <summary>
		/// Clean Up Used Resources.
		/// </summary>
		~Home()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  chooseFileButton;
	private: System::Windows::Forms::Label^  fileNameLabel;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TextBox^  durationTextBox;
	private: System::Windows::Forms::ComboBox^  algorithmsComboBox;
	private: System::Windows::Forms::Button^  runButton;
	private: System::Windows::Forms::Panel^  mainPanel;
	private: System::Windows::Forms::CheckBox^  allowCopyCheck;
	private: String^ fileLocation;
	private: System::Windows::Forms::Label^  outputLabel;




	protected:

	protected:

	protected:



	protected:

	private:
		/// <summary>
		/// Required Designer Variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for designer support.
		/// The content of the method must not be changed with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Home::typeid));
			this->chooseFileButton = (gcnew System::Windows::Forms::Button());
			this->fileNameLabel = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->durationTextBox = (gcnew System::Windows::Forms::TextBox());
			this->algorithmsComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->runButton = (gcnew System::Windows::Forms::Button());
			this->mainPanel = (gcnew System::Windows::Forms::Panel());
			this->outputLabel = (gcnew System::Windows::Forms::Label());
			this->allowCopyCheck = (gcnew System::Windows::Forms::CheckBox());
			this->mainPanel->SuspendLayout();
			this->SuspendLayout();
			// 
			// chooseFileButton
			// 
			this->chooseFileButton->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->chooseFileButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->chooseFileButton->Location = System::Drawing::Point(132, 185);
			this->chooseFileButton->Margin = System::Windows::Forms::Padding(0);
			this->chooseFileButton->Name = L"chooseFileButton";
			this->chooseFileButton->Size = System::Drawing::Size(100, 31);
			this->chooseFileButton->TabIndex = 0;
			this->chooseFileButton->Text = L"Choose File";
			this->chooseFileButton->UseVisualStyleBackColor = true;
			this->chooseFileButton->Click += gcnew System::EventHandler(this, &Home::chooseFile);
			// 
			// fileNameLabel
			// 
			this->fileNameLabel->AllowDrop = true;
			this->fileNameLabel->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->fileNameLabel->BackColor = System::Drawing::Color::White;
			this->fileNameLabel->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->fileNameLabel->Location = System::Drawing::Point(28, 185);
			this->fileNameLabel->Margin = System::Windows::Forms::Padding(0);
			this->fileNameLabel->Name = L"fileNameLabel";
			this->fileNameLabel->Size = System::Drawing::Size(104, 31);
			this->fileNameLabel->TabIndex = 1;
			this->fileNameLabel->Text = L"Drag File Here";
			this->fileNameLabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->fileNameLabel->DragDrop += gcnew System::Windows::Forms::DragEventHandler(this, &Home::fileDrop);
			this->fileNameLabel->DragEnter += gcnew System::Windows::Forms::DragEventHandler(this, &Home::dragEnter);
			// 
			// label1
			// 
			this->label1->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(28, 69);
			this->label1->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(115, 17);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Desired Duration";
			// 
			// durationTextBox
			// 
			this->durationTextBox->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->durationTextBox->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->durationTextBox->Location = System::Drawing::Point(32, 89);
			this->durationTextBox->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->durationTextBox->Name = L"durationTextBox";
			this->durationTextBox->Size = System::Drawing::Size(199, 22);
			this->durationTextBox->TabIndex = 3;
			this->durationTextBox->Text = L"Minutes/Folder";
			this->durationTextBox->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->durationTextBox->Enter += gcnew System::EventHandler(this, &Home::removeHint);
			this->durationTextBox->Leave += gcnew System::EventHandler(this, &Home::checkHint);
			// 
			// algorithmsComboBox
			// 
			this->algorithmsComboBox->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->algorithmsComboBox->FormattingEnabled = true;
			this->algorithmsComboBox->Location = System::Drawing::Point(32, 137);
			this->algorithmsComboBox->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->algorithmsComboBox->Name = L"algorithmsComboBox";
			this->algorithmsComboBox->Size = System::Drawing::Size(199, 24);
			this->algorithmsComboBox->TabIndex = 4;
			this->algorithmsComboBox->Text = L"Choose Algorithm";
			this->algorithmsComboBox->SelectedIndexChanged += gcnew System::EventHandler(this, &Home::algorithmsComboBox_SelectedIndexChanged);
			// 
			// runButton
			// 
			this->runButton->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->runButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->runButton->Location = System::Drawing::Point(32, 267);
			this->runButton->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->runButton->Name = L"runButton";
			this->runButton->Size = System::Drawing::Size(200, 31);
			this->runButton->TabIndex = 5;
			this->runButton->Text = L"Run";
			this->runButton->UseVisualStyleBackColor = true;
			this->runButton->Click += gcnew System::EventHandler(this, &Home::run);
			// 
			// mainPanel
			// 
			this->mainPanel->AllowDrop = true;
			this->mainPanel->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->mainPanel->Controls->Add(this->outputLabel);
			this->mainPanel->Controls->Add(this->allowCopyCheck);
			this->mainPanel->Controls->Add(this->label1);
			this->mainPanel->Controls->Add(this->runButton);
			this->mainPanel->Controls->Add(this->chooseFileButton);
			this->mainPanel->Controls->Add(this->algorithmsComboBox);
			this->mainPanel->Controls->Add(this->fileNameLabel);
			this->mainPanel->Controls->Add(this->durationTextBox);
			this->mainPanel->Location = System::Drawing::Point(29, 1);
			this->mainPanel->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->mainPanel->Name = L"mainPanel";
			this->mainPanel->Size = System::Drawing::Size(267, 383);
			this->mainPanel->TabIndex = 6;
			// 
			// outputLabel
			// 
			this->outputLabel->Location = System::Drawing::Point(4, 304);
			this->outputLabel->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->outputLabel->Name = L"outputLabel";
			this->outputLabel->Size = System::Drawing::Size(259, 28);
			this->outputLabel->TabIndex = 7;
			this->outputLabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// allowCopyCheck
			// 
			this->allowCopyCheck->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->allowCopyCheck->AutoSize = true;
			this->allowCopyCheck->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->allowCopyCheck->Location = System::Drawing::Point(76, 231);
			this->allowCopyCheck->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->allowCopyCheck->Name = L"allowCopyCheck";
			this->allowCopyCheck->Size = System::Drawing::Size(94, 21);
			this->allowCopyCheck->TabIndex = 7;
			this->allowCopyCheck->Text = L"Allow Copy";
			this->allowCopyCheck->UseVisualStyleBackColor = true;
			// 
			// Home
			// 
			this->AccessibleName = L"Sound Packer";
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(323, 373);
			this->Controls->Add(this->mainPanel);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->MaximizeBox = false;
			this->MaximumSize = System::Drawing::Size(341, 420);
			this->MinimumSize = System::Drawing::Size(341, 420);
			this->Name = L"Home";
			this->Text = L"Sound Packer";
			this->mainPanel->ResumeLayout(false);
			this->mainPanel->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void chooseFile(System::Object^  sender, System::EventArgs^  e) {
		OpenFileDialog^ openFileDialog = gcnew OpenFileDialog;

		openFileDialog->InitialDirectory = "c:\\";
		openFileDialog->Filter = "txt files (*.txt)|*.txt|All files (*.*)|*.*";
		openFileDialog->FilterIndex = 1;
		openFileDialog->RestoreDirectory = true;

		if (openFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			fileNameLabel->Text = openFileDialog->SafeFileName;
			fileLocation = openFileDialog->FileName;
		}
	}

	private: System::Void removeHint(System::Object^  sender, System::EventArgs^  e) {
		if (durationTextBox->Text == "Minutes/Folder") {
			durationTextBox->Text = "";
		}
	}

	private: System::Void checkHint(System::Object^  sender, System::EventArgs^  e) {
		if (durationTextBox->Text->Length == 0) {
			durationTextBox->Text = "Minutes/Folder";
		}
	}
	
	private: System::Void dragEnter(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e) {
		e->Effect = DragDropEffects::All;
	}

	private: System::Void fileDrop(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e) {
		array<String^>^ files = (array<String^>^)e->Data->GetData(DataFormats::FileDrop, false);
		fileLocation = files[0];
		array<String^>^ locationSplit = files[0]->Split('\\');
		fileNameLabel->Text = locationSplit[locationSplit->Length - 1];
	}

	private: bool checkValidArgs() {
		durationTextBox->Text = durationTextBox->Text->Trim();
		String^ duration = durationTextBox->Text;

		if (duration->Length == 0 || duration == "Minutes/Folder") {
			outputLabel->Text = "Please Enter the Desired Duration";
			return false;
		}
		else if (algorithmsComboBox->SelectedIndex == -1) {
			outputLabel->Text = "Please Select an Algorithm";
			return false;
		}
		else if (!fileLocation) {
			outputLabel->Text = "Please Select an input File";
			return false;
		}

		return true;
	}

	private: System::Void run(System::Object^  sender, System::EventArgs^  e) {
		if (!checkValidArgs())
			return;

		msclr::interop::marshal_context context;
		std::string chosenFile = context.marshal_as<std::string>(fileLocation);
		std::string chosenAlgorithm = context.marshal_as<std::string>(Convert::ToString(algorithmsComboBox->SelectedItem));
		float duration = Convert::ToDouble(durationTextBox->Text);
		bool allowCopy = allowCopyCheck->Checked;
		
		Double timeElapsed = runAlgorithm(chosenFile, chosenAlgorithm, duration, allowCopy);
		outputLabel->Text = "Time Elapsed: " + timeElapsed.ToString();
	}
private: System::Void algorithmsComboBox_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
}
};
}
