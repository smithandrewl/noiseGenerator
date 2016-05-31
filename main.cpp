#include <TGUI/TGUI.hpp>

void loadWidgets(tgui::Gui& gui) {
    auto theme = std::make_shared<tgui::Theme>("TGUI/widgets/Black.txt");
    tgui::Button::Ptr button = theme->load("Button");

    button->setText("Hello Button World!");
    button->setSize({200, 50});
    button->setPosition(200, 100);

    gui.add(button);
}

int main()
{
    sf::RenderWindow window{{800, 600}, "Noise Maker"};
    tgui::Gui gui{window}; // Create the gui and attach it to the window
    loadWidgets(gui);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            gui.handleEvent(event); // Pass the event to the widgets
        }

        window.clear();
        gui.draw(); // Draw all widgets
        window.display();
    }
}
