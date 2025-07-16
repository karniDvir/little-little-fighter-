#include "Controller.h"
//---------------------------------------

void Controller::run()
{
    try { initBoardObj(); }
    catch (std::exception& ex) { }
    m_window.setFramerateLimit(60);
    try {
        m_menu.initMenu(m_window);
        m_merchant.initMerchnt(m_window);
        if (!m_menu.runMenu(m_window, m_board.getPLayer(), m_bar))
            return;
        if (!m_merchant.runMerchant(m_window, m_board.getPLayer(), m_bar))
            return;
        sf::Clock clock;
        while (m_window.isOpen())
        {
            draw();
            sf::Time elapsd = clock.getElapsedTime();
            m_board.moveObj(elapsd);
            m_bar.updateBar(m_board.getPLayer());
            if (!handeLevelStatus())
            {
                break;
            }
            //    m_window.setFramerateLimit(60);
            for (auto event = sf::Event{}; m_window.pollEvent(event);)
            {
                switch (event.type)
                {
                case sf::Event::Closed:
                    m_window.close();
                    break;
                }
            }
            if (elapsd.asSeconds() > 0.1)
                clock.restart();
        }
    }
    catch (std::exception& ex)
    {
        std::cout << ex.what() << "from run\n";
        return;
    }
    catch (const std::out_of_range& ex) { return;}
}
//------------------------------------------------------------------------------
void Controller::initBoardObj()
{
    m_board.initBoard();
    m_window.clear();
    m_window.create(sf::VideoMode(MAX_SIZE_COL, MAX_SIZE_ROW), "window");
    DataManager::instence().setWindowPosition(m_window.getPosition());
}

//-------------------------------------------------------------
void Controller::changeLevel()
{
   
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    m_board.changelevel();
    draw(NEXT_LEVEL);
    if(DataManager::instence().getLevelStatus() == NEXT_LEVEL) //karni
        if (!m_merchant.runMerchant(m_window, m_board.getPLayer(), m_bar))
            return;
}
//will return if the game needs to end
//-----------------------------------------------------------
bool Controller::handeLevelStatus()
{
    auto type = DataManager::instence().getLevelStatus();
    switch (type)
    {
    case CURRENT_LEVEL:                      return true;
    case NEXT_LEVEL:    changeLevel();       return true;// false
    case GAME_OVER:    EndGameWindow(false); return false;
    case WIN_GAME:     EndGameWindow(true);  return false;
    default:                                return true;
    }
    return false;
}
//--------------------------------------------------------
void Controller::draw(const LevelType& level )
{

    static sf::Vector2f defaultCenter = m_window.getView().getCenter();
   // std::cout << "Default View Center: (" << defaultCenter.x << ", " << defaultCenter.y << ")" << std::endl;

    auto viewSize = sf::Vector2f(float(m_window.getSize().x), float(m_window.getSize().y));
    auto playerPlace = DataManager::instence().getPlayerPosition();
    float x = playerPlace.x;
    playerPlace.x -= 50;
    playerPlace.y = 400;
    sf::View view0;
    if(level == NEXT_LEVEL && x < 550)
         view0 = sf::View(defaultCenter, viewSize);
    else
         view0 = sf::View(playerPlace, viewSize);
    view0.setViewport({ 0.f, 0.f, 1.f, 1.f });
    m_window.clear();
    if(x > 550 && x < 1900 || level == NEXT_LEVEL)// for following after player
        m_window.setView(view0);
    m_board.draw(m_window);
    if (x < 550)
        x = 0;
    else if (x > 1900)
        x = 1350;
    else
        x -= 550;
    m_bar.draw(m_window,x); // to fix
    m_window.display();
}
//----------------------------------------------------
void Controller::EndGameWindow(bool Iswin)
{
    m_board.GameOver();
    m_endGameScreen.initScreen(Iswin);
    m_endGameScreen.runEndGame(m_window); //karni
    return;
}