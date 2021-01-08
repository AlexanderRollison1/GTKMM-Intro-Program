//Alexander Rollison
#include <gtkmm.h>
#include <iostream>

class MyWindow : public Gtk::Window
{
	public:
		MyWindow();										//Constructor
		void on_Cancel_Button_click();					//CANCEL Button
		void on_Ok_Button_click(Gtk::Entry *MyEntry);	//OK Button
};

int main(int argc, char *argv[])
{
	auto app = Gtk::Application::create(argc, argv, "");	//one
	//Create Window to run
	MyWindow RunWindow;										//two
	//run
	return app->run(RunWindow);								//three
}

MyWindow::MyWindow()
{
	set_default_size(800,600);
	set_title("Guess the Place!");
	set_position(Gtk::WIN_POS_CENTER);
	set_border_width(10);
	
	//create main vertical box
	Gtk::Box *Vbox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 0));
	add(*Vbox);
	
	//creating menus
	Gtk::MenuBar *MyHintBar = Gtk::manage(new Gtk::MenuBar());
	Vbox->pack_start(*MyHintBar, Gtk::PACK_SHRINK, 0);
	Gtk::MenuItem *MyHint1Menu = Gtk::manage(new Gtk::MenuItem("_Mount Fuji", true));
	Gtk::MenuItem *MyHint2Menu = Gtk::manage(new Gtk::MenuItem("_Yokohama", true));
	Gtk::MenuItem *MyHint3Menu = Gtk::manage(new Gtk::MenuItem("_Sky Tree", true));
	
	//appending menus
	MyHintBar->append(*MyHint1Menu);
	MyHintBar->append(*MyHint2Menu);
	MyHintBar->append(*MyHint3Menu);
	
	//First menu
	Gtk::Menu *MyHintSub1Menu = Gtk::manage(new Gtk::Menu());
	MyHint1Menu->set_submenu(*MyHintSub1Menu);
	Gtk::MenuItem *SubMenuItem_One = Gtk::manage(new Gtk::MenuItem("3,776 meters", true));
	MyHintSub1Menu->append(*SubMenuItem_One);
	Gtk::MenuItem *SubMenuItem_Two = Gtk::manage(new Gtk::MenuItem("Volcano", true));
	MyHintSub1Menu->append(*SubMenuItem_Two);
	
	//Second menu
	Gtk::Menu *MyHintSub2Menu = Gtk::manage(new Gtk::Menu());
	MyHint2Menu->set_submenu(*MyHintSub2Menu);
	Gtk::MenuItem *SubMenuItem_Three = Gtk::manage(new Gtk::MenuItem("DeNA BayStars", true));
	MyHintSub2Menu->append(*SubMenuItem_Three);
	Gtk::MenuItem *SubMenuItem_Four = Gtk::manage(new Gtk::MenuItem("China Town", true));
	MyHintSub2Menu->append(*SubMenuItem_Four);
	
	//Third menu
	Gtk::Menu *MyHintSub3Menu = Gtk::manage(new Gtk::Menu());
	MyHint3Menu->set_submenu(*MyHintSub3Menu);
	Gtk::MenuItem *SubMenuItem_Five = Gtk::manage(new Gtk::MenuItem("Tokyo", true));
	MyHintSub3Menu->append(*SubMenuItem_Five);
	
	//Create label
	Gtk::Label *MyLabel = Gtk::manage(new Gtk::Label("What place does this flag correspond to? (Hints on the top left of the screen)"));
	Vbox->pack_start(*MyLabel);
	
	//Create Image
	Gtk::Image *MyImage = Gtk::manage(new Gtk::Image{"Japan.png"});
	Vbox->add(*MyImage);
	
	//1: Create Horizontal box 2: Create 2 Vertical boxes. 
	Gtk::Box *Hbox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 0));
	Vbox->pack_end(*Hbox);
	Gtk::Box *VboxButton = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 0));
	Gtk::Box *VboxEntry = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 0));
	Hbox->pack_start(*VboxButton);
	Hbox->pack_start(*VboxEntry);
	
	//Create Entry and use grab_focus to highlight if true
	Gtk::Entry *MyEntry = Gtk::manage(new Gtk::Entry());
	MyEntry->set_text("Enter Guess Here");
    	MyEntry->set_activates_default(true);
	VboxEntry->add(*MyEntry);
	MyEntry->grab_focus();
	MyEntry->signal_activate().connect(sigc::bind<Gtk::Entry*>(sigc::mem_fun(*this, &MyWindow::on_Ok_Button_click), MyEntry));
	
	//Create OK and CANCEL buttons.
	Gtk::Button* buttonOK = new Gtk::Button("Ok");
	Gtk::Button* buttonCANCEL = new Gtk::Button("Cancel");
	
	VboxButton->add(*buttonOK);
	VboxButton->add(*buttonCANCEL);
	buttonOK->set_border_width(3);
	buttonCANCEL->set_border_width(3);
	buttonOK->signal_clicked().connect(sigc::bind<Gtk::Entry*>(sigc::mem_fun(*this, &MyWindow::on_Ok_Button_click), MyEntry));
	buttonCANCEL->signal_clicked().connect(sigc::mem_fun(*this,&MyWindow::on_Cancel_Button_click));

	Vbox->show_all();
}

void MyWindow::on_Ok_Button_click(Gtk::Entry *MyEntry)
{
	if(MyEntry->get_text() == "Japan")
	{
		Gtk::MessageDialog *CORRECT= new Gtk::MessageDialog{"You guessed <span fgcolor='#0000ff'>correctly</span>!!",true, Gtk::MESSAGE_WARNING,Gtk::BUTTONS_OK, false};
		CORRECT->run();
		hide();
	}
	else
	{
		MyEntry->get_text();
		Gtk::MessageDialog *INCORRECT= new Gtk::MessageDialog{"Your answer is not <span fgcolor='#ff0000'>correct</span>.\nPlease try again",true, Gtk::MESSAGE_ERROR,Gtk::BUTTONS_OK, false};
		INCORRECT->run();
		INCORRECT->hide();
	}
}

void MyWindow::on_Cancel_Button_click()
{
    hide(); // will close the program when clicked
}
