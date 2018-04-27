#pragma once
#include "HelperFunctions.h"
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








	private: String ^ fileLocation;
    private: System::Windows::Forms::TextBox^  durationTextBox;
    private: System::Windows::Forms::Label^  fileNameLabel;
    private: System::Windows::Forms::ComboBox^  algorithmsComboBox;
    private: System::Windows::Forms::Button^  chooseFileButton;
    private: System::Windows::Forms::Button^  runButton;
    private: System::Windows::Forms::Label^  label1;
    private: System::Windows::Forms::CheckBox^  allowCopyCheck;
    private: System::Windows::Forms::Label^  outputLabel;

    private: System::Windows::Forms::CheckBox^  multithreadingCheckBox;
    private: System::Windows::Forms::Label^  packerTitle;
    private: System::Windows::Forms::Label^  soundTitle;








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
            this->durationTextBox = (gcnew System::Windows::Forms::TextBox());
            this->fileNameLabel = (gcnew System::Windows::Forms::Label());
            this->algorithmsComboBox = (gcnew System::Windows::Forms::ComboBox());
            this->chooseFileButton = (gcnew System::Windows::Forms::Button());
            this->runButton = (gcnew System::Windows::Forms::Button());
            this->label1 = (gcnew System::Windows::Forms::Label());
            this->allowCopyCheck = (gcnew System::Windows::Forms::CheckBox());
            this->outputLabel = (gcnew System::Windows::Forms::Label());
            this->multithreadingCheckBox = (gcnew System::Windows::Forms::CheckBox());
            this->packerTitle = (gcnew System::Windows::Forms::Label());
            this->soundTitle = (gcnew System::Windows::Forms::Label());
            this->SuspendLayout();
            // 
            // durationTextBox
            // 
            this->durationTextBox->Anchor = System::Windows::Forms::AnchorStyles::None;
            this->durationTextBox->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
            this->durationTextBox->Location = System::Drawing::Point(44, 89);
            this->durationTextBox->Name = L"durationTextBox";
            this->durationTextBox->Size = System::Drawing::Size(250, 20);
            this->durationTextBox->TabIndex = 3;
            this->durationTextBox->Text = L"HH:MM:SS";
            this->durationTextBox->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
            this->durationTextBox->Enter += gcnew System::EventHandler(this, &Home::removeHint);
            this->durationTextBox->Leave += gcnew System::EventHandler(this, &Home::checkHint);
            // 
            // fileNameLabel
            // 
            this->fileNameLabel->AllowDrop = true;
            this->fileNameLabel->Anchor = System::Windows::Forms::AnchorStyles::None;
            this->fileNameLabel->BackColor = System::Drawing::Color::White;
            this->fileNameLabel->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->fileNameLabel->ForeColor = System::Drawing::Color::Black;
            this->fileNameLabel->Location = System::Drawing::Point(45, 180);
            this->fileNameLabel->Margin = System::Windows::Forms::Padding(0);
            this->fileNameLabel->Name = L"fileNameLabel";
            this->fileNameLabel->Size = System::Drawing::Size(170, 25);
            this->fileNameLabel->TabIndex = 1;
            this->fileNameLabel->Text = L"Drag File Here";
            this->fileNameLabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
            this->fileNameLabel->DragDrop += gcnew System::Windows::Forms::DragEventHandler(this, &Home::fileDrop);
            this->fileNameLabel->DragEnter += gcnew System::Windows::Forms::DragEventHandler(this, &Home::dragEnter);
            // 
            // algorithmsComboBox
            // 
            this->algorithmsComboBox->Anchor = System::Windows::Forms::AnchorStyles::None;
            this->algorithmsComboBox->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->algorithmsComboBox->FormattingEnabled = true;
            this->algorithmsComboBox->Location = System::Drawing::Point(44, 135);
            this->algorithmsComboBox->Name = L"algorithmsComboBox";
            this->algorithmsComboBox->Size = System::Drawing::Size(250, 21);
            this->algorithmsComboBox->TabIndex = 4;
            this->algorithmsComboBox->Text = L"Choose Algorithm";
            this->algorithmsComboBox->SelectedIndexChanged += gcnew System::EventHandler(this, &Home::selectedAlgorithmChanged);
            // 
            // chooseFileButton
            // 
            this->chooseFileButton->Anchor = System::Windows::Forms::AnchorStyles::None;
            this->chooseFileButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(157)),
                static_cast<System::Int32>(static_cast<System::Byte>(213)));
            this->chooseFileButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->chooseFileButton->ForeColor = System::Drawing::Color::White;
            this->chooseFileButton->Location = System::Drawing::Point(214, 180);
            this->chooseFileButton->Margin = System::Windows::Forms::Padding(0);
            this->chooseFileButton->Name = L"chooseFileButton";
            this->chooseFileButton->Size = System::Drawing::Size(80, 25);
            this->chooseFileButton->TabIndex = 0;
            this->chooseFileButton->Text = L"Choose File";
            this->chooseFileButton->UseVisualStyleBackColor = false;
            this->chooseFileButton->Click += gcnew System::EventHandler(this, &Home::chooseFile);
            // 
            // runButton
            // 
            this->runButton->Anchor = System::Windows::Forms::AnchorStyles::None;
            this->runButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(157)),
                static_cast<System::Int32>(static_cast<System::Byte>(213)));
            this->runButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->runButton->Location = System::Drawing::Point(44, 274);
            this->runButton->Name = L"runButton";
            this->runButton->Size = System::Drawing::Size(250, 30);
            this->runButton->TabIndex = 5;
            this->runButton->Text = L"Run";
            this->runButton->UseVisualStyleBackColor = false;
            this->runButton->Click += gcnew System::EventHandler(this, &Home::run);
            // 
            // label1
            // 
            this->label1->Anchor = System::Windows::Forms::AnchorStyles::None;
            this->label1->AutoSize = true;
            this->label1->Font = (gcnew System::Drawing::Font(L"Arial", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->label1->Location = System::Drawing::Point(41, 72);
            this->label1->Name = L"label1";
            this->label1->Size = System::Drawing::Size(86, 14);
            this->label1->TabIndex = 2;
            this->label1->Text = L"Duration / Folder";
            // 
            // allowCopyCheck
            // 
            this->allowCopyCheck->Anchor = System::Windows::Forms::AnchorStyles::None;
            this->allowCopyCheck->AutoSize = true;
            this->allowCopyCheck->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(38)), static_cast<System::Int32>(static_cast<System::Byte>(38)),
                static_cast<System::Int32>(static_cast<System::Byte>(46)));
            this->allowCopyCheck->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->allowCopyCheck->ForeColor = System::Drawing::Color::Transparent;
            this->allowCopyCheck->Location = System::Drawing::Point(73, 232);
            this->allowCopyCheck->Name = L"allowCopyCheck";
            this->allowCopyCheck->Size = System::Drawing::Size(75, 17);
            this->allowCopyCheck->TabIndex = 7;
            this->allowCopyCheck->Text = L"Allow Copy";
            this->allowCopyCheck->UseVisualStyleBackColor = false;
            // 
            // outputLabel
            // 
            this->outputLabel->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->outputLabel->Location = System::Drawing::Point(68, 323);
            this->outputLabel->Name = L"outputLabel";
            this->outputLabel->Size = System::Drawing::Size(194, 23);
            this->outputLabel->TabIndex = 7;
            this->outputLabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
            // 
            // multithreadingCheckBox
            // 
            this->multithreadingCheckBox->AutoSize = true;
            this->multithreadingCheckBox->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(38)),
                static_cast<System::Int32>(static_cast<System::Byte>(38)), static_cast<System::Int32>(static_cast<System::Byte>(46)));
            this->multithreadingCheckBox->Enabled = false;
            this->multithreadingCheckBox->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->multithreadingCheckBox->Location = System::Drawing::Point(173, 232);
            this->multithreadingCheckBox->Name = L"multithreadingCheckBox";
            this->multithreadingCheckBox->Size = System::Drawing::Size(89, 17);
            this->multithreadingCheckBox->TabIndex = 8;
            this->multithreadingCheckBox->Text = L"Multithreading";
            this->multithreadingCheckBox->UseVisualStyleBackColor = false;
            // 
            // packerTitle
            // 
            this->packerTitle->AutoSize = true;
            this->packerTitle->Font = (gcnew System::Drawing::Font(L"Arial", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->packerTitle->Location = System::Drawing::Point(70, 14);
            this->packerTitle->Margin = System::Windows::Forms::Padding(0);
            this->packerTitle->Name = L"packerTitle";
            this->packerTitle->Size = System::Drawing::Size(77, 19);
            this->packerTitle->TabIndex = 9;
            this->packerTitle->Text = L"PACKER";
            // 
            // soundTitle
            // 
            this->soundTitle->AutoSize = true;
            this->soundTitle->Font = (gcnew System::Drawing::Font(L"Arial", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->soundTitle->Location = System::Drawing::Point(10, 14);
            this->soundTitle->Name = L"soundTitle";
            this->soundTitle->Size = System::Drawing::Size(65, 18);
            this->soundTitle->TabIndex = 10;
            this->soundTitle->Text = L"SOUND";
            // 
            // Home
            // 
            this->AccessibleName = L"Sound Packer";
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(38)), static_cast<System::Int32>(static_cast<System::Byte>(38)),
                static_cast<System::Int32>(static_cast<System::Byte>(46)));
            this->ClientSize = System::Drawing::Size(334, 411);
            this->Controls->Add(this->packerTitle);
            this->Controls->Add(this->multithreadingCheckBox);
            this->Controls->Add(this->outputLabel);
            this->Controls->Add(this->runButton);
            this->Controls->Add(this->allowCopyCheck);
            this->Controls->Add(this->durationTextBox);
            this->Controls->Add(this->label1);
            this->Controls->Add(this->fileNameLabel);
            this->Controls->Add(this->algorithmsComboBox);
            this->Controls->Add(this->chooseFileButton);
            this->Controls->Add(this->soundTitle);
            this->ForeColor = System::Drawing::Color::White;
            this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
            this->MaximizeBox = false;
            this->MaximumSize = System::Drawing::Size(350, 450);
            this->MinimumSize = System::Drawing::Size(350, 450);
            this->Name = L"Home";
            this->Text = L"Sound Packer";
            this->ResumeLayout(false);
            this->PerformLayout();

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
			if (durationTextBox->Text == "HH:MM:SS") {
				durationTextBox->Text = "";
			}
		}

		private: System::Void checkHint(System::Object^  sender, System::EventArgs^  e) {
			if (durationTextBox->Text->Length == 0) {
				durationTextBox->Text = "HH:MM:SS";
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

		private: bool isValidDurationString(String^ duration) {
			if (duration->Length != 8)
				return false;

			if (duration[2] != ':' || duration[5] != ':')
				return false;

			for (int i = 0; i < 8; ++i) {
				if (i == 2 || i == 5)
					continue;
				if (Char::IsDigit(duration, i) == false)
					return false;
			}

			return true;
		}

		private: bool checkValidArgs() {
			durationTextBox->Text = durationTextBox->Text->Trim();
			String^ duration = durationTextBox->Text;

			if (!isValidDurationString(duration)) {
				outputLabel->Text = "Please Enter a Valid Duration";
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
			std::string durationString = context.marshal_as<std::string>(Convert::ToString(durationTextBox->Text));
			int duration = parseDurationString(durationString);
			bool allowCopy = allowCopyCheck->Checked;
            bool multithreading = multithreadingCheckBox->Checked;

			Double timeElapsed = runAlgorithm(chosenFile, chosenAlgorithm, duration, allowCopy, multithreading);
			outputLabel->Text = "Time Elapsed: " + timeElapsed.ToString() + " Seconds";
		}

        private: System::Void selectedAlgorithmChanged(System::Object^  sender, System::EventArgs^  e) {
            msclr::interop::marshal_context context;
            std::string chosenAlgorithm = context.marshal_as<std::string>(Convert::ToString(algorithmsComboBox->SelectedItem));

            if (chosenAlgorithm == WORST_FIT_DEC_LS || chosenAlgorithm == WORST_FIT_DEC_PQ ||
                chosenAlgorithm == FIRST_FIT) {
                multithreadingCheckBox->Enabled = true;
            } else {
                multithreadingCheckBox->Enabled = false;
                multithreadingCheckBox->Checked = false;
            }
        }
    };
}