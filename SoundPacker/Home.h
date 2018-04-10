#pragma once

namespace SoundPacker {

	using namespace System;
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
			//
			// TODO: Add constructor code here.
			//
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
			this->SuspendLayout();
			// 
			// Home
			// 
			this->AccessibleName = L"Sound Packer";
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 261);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"Home";
			this->Text = L"Sound Packer";
			this->ResumeLayout(false);

		}
#pragma endregion
	};
}
