#include <stdexcept>

#include "SGUI.h"

#include "SGField.h"
#include "SGGame.h"
#include "SGPlayer.h"
#include "SGSettings.h"
#include <locale.h>
struct GameExit : std::exception {};

static const char*  bool_to_str(bool b) { return b ? "enabled" : "disabled"; }

template<typename Functor>
void MainMenu::display_menu(std::vector<MenuItem>& p_menu_items, Functor p_selected_item_handler, bool p_quit_with_q, std::string p_title)
{
    for (std::size_t i = 0; i < p_menu_items.size(); ++i)
    {
        //p_menu_items[i].pos = { 10 + (int)i, (40 - (int)p_menu_items[i].label.length()) / 2 };
        p_menu_items[i].pos = { 10 + (int)i, 30};
    }

    try
    {
        erase();
        menu_item_t selected_item = 0;
        bool is_selected = false;
        while (true)
        {
            //mvprintw(LINES / 4, (COLS - p_title.length()) / 2, p_title.c_str());
            mvprintw(5, 20, p_title.c_str());

            for (std::size_t i = 0; i < p_menu_items.size(); ++i)
            {
                mvprintw(p_menu_items[i].pos.y, p_menu_items[i].pos.x, p_menu_items[i].label.c_str());
            }

            // make the currently selected item standout
            mvchgat(p_menu_items[selected_item].pos.y, p_menu_items[selected_item].pos.x, p_menu_items[selected_item].label.length(), A_STANDOUT, 0, NULL);
            refresh();

            switch (getch())
            {
            case KEY_UP:
                selected_item = selected_item != 0 ? selected_item - 1 : p_menu_items.size() - 1;
                break;
            case KEY_DOWN:
                selected_item = selected_item != (int)p_menu_items.size() - 1 ? selected_item + 1 : 0;
                break;
            case '\n':
                is_selected = true;
                break;
            case 'q':
            case 27:
                if (p_quit_with_q) throw GameExit();
                break;
            }

            if (is_selected)
            {
                p_selected_item_handler(selected_item);
                is_selected = false;
                erase();
            }
        }
    }
    // exit the game, if it's called for an exit
    catch (const GameExit&) {}
}

void MainMenu::new_game()
{



    auto original_func = []()
    {

        auto create_newwin = [&](int height, int width, int starty, int startx)
        {
            WINDOW* local_win;

            local_win = newwin(height, width, starty, startx);
            //wborder(local_win, '|', '|', '-', '-', '+', '+', '+', '+');
            //wrefresh(local_win);
            return local_win;
        };


        auto destroy_win = [&](WINDOW* local_win)
        {
            wborder(local_win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
            wrefresh(local_win);
            delwin(local_win);
        };

        erase();
        refresh();

        int wall_width_top = 2;
        int wall_width_bottom = 2;
        int wall_width_left = 3;
        int wall_width_right = 3;


        int wind_game_field_height = 20;
        int wind_game_field_width = 50;
     

        int wind_game_field_start_y = 0 ;
        int wind_game_field_start_x = 0 ;
                
        int wind_game_field_end_y = wind_game_field_start_y + wind_game_field_height;
        int wind_game_field_end_x = wind_game_field_start_x + wind_game_field_width;




        int wind_game_start_y = wind_game_field_start_y + wall_width_top;
        int wind_game_start_x = wind_game_field_start_x + wall_width_left;

        int wind_game_end_y = wind_game_field_end_y - wall_width_bottom;
        int wind_game_end_x = wind_game_field_end_x - wall_width_right;

        int wind_game_height = wind_game_end_y - wind_game_start_y;
        int wind_game_width = wind_game_end_x - wind_game_start_x;


        auto  game_field_win = create_newwin(wind_game_field_height, wind_game_field_width, wind_game_field_start_y, wind_game_field_start_x);
        auto  game_win = create_newwin(wind_game_height, wind_game_width, wind_game_start_y, wind_game_start_x);


        GameUI game_ui{ game_win, game_field_win };
        Game game(game_ui);
        game.start();

        delwin(game_field_win);
        delwin(game_win);

    };
        

    original_func();

    auto test_basic_1 = []()
    {
        initscr();
        printw("Hello World !!!");
        refresh();
        getch();
        endwin();
    };          
    auto test_basic_2 = []()
    {
        initscr();
        start_color();
        //pair number, foreground, background
        init_pair(1, COLOR_RED, COLOR_WHITE);
        attron(COLOR_PAIR(1));
        printw("Hello World color!!!");
        attroff(COLOR_PAIR(1));
        refresh();
        getch();
        endwin();
    }; 
    auto test_basic_3 = []()
    {
        int ch;
        initscr();
        raw();
        keypad(stdscr, TRUE);
        noecho();

        ch = getch();
        if (ch == KEY_F(1)) 
        {
            printw("F1 Key pressed");
        }
        else
        {
            printw("The pressed key is ");
            attron(A_BOLD);
            printw("%c", ch);
            attroff(A_BOLD);
        }

        refresh();
        getch();
        endwin();

    };  
    auto test_basic_4 = []()
    {
        int row, col;

        initscr();

        resize_term(20, 30);

        getmaxyx(stdscr, row, col);
        resize_term(row, col);
        getmaxyx(stdscr, row, col);

        getmaxyx(stdscr, row, col);
        mvprintw(0, 0, "Screen size: rows %d, columns %d", row, col);
        refresh();
        getch();
        endwin();
    };        
    auto test_basic_5 = []()
    {
        auto create_newwin = [&](int height, int width, int starty, int startx)
        {
            WINDOW* local_win;

            local_win = newwin(height, width, starty, startx);
            wborder(local_win, '|', '|', '-', '-', '+', '+', '+', '+');
            wrefresh(local_win);
            return local_win;
        };

        auto destroy_win = [&](WINDOW* local_win)
        {
            wborder(local_win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
            wrefresh(local_win);
            delwin(local_win);
        };

        WINDOW* local_win;
        initscr();
        start_color();
        init_pair(1, COLOR_RED, COLOR_BLACK);
        attron(COLOR_PAIR(1));
        printw("Hello Pdcurse !!!");
        attroff(COLOR_PAIR(1));
        mvaddstr(6, 32, "Test");
        refresh();
        local_win = create_newwin(10, 15, 5, 5);
        getch();
        destroy_win(local_win);
        getch();
    };    
    auto test_basic_6 = []()
    {


        int player_input;
        char player_label = '@';
        char player_back_footprint = ' ';

        int player_init_x = 10;
        int player_init_y = 10;
        
        int player_curr_x = player_init_x;
        int player_curr_y = player_init_y;

        int window_curr_height = 0;
        int window_curr_width = 0;


        //trigger/open the standard scrren 
        auto open_window = [&]
        {
            initscr();
            keypad(stdscr, TRUE);
            noecho();
            curs_set(FALSE);
        };
        
        //show player initial position on the screen
        auto displ_player_init_pos = [&]()
        {
            initscr();
            keypad(stdscr, TRUE);
            noecho();
            curs_set(FALSE);
            mvaddch(player_init_x, player_init_y, player_label);
        };

        //move to a given direction 
        auto mv_to_dir = [&](int mv_dir)
        {
            //mask the previous location of the player with "space"
            mvaddch(player_curr_y, player_curr_x, player_back_footprint);

            //step to the advance the player
            switch (mv_dir)
            {

            case KEY_LEFT:
                --player_curr_x;
                break;

            case KEY_RIGHT:
                ++player_curr_x;
                break;


            case KEY_UP:
                --player_curr_y;
                break;


            case KEY_DOWN:
                ++player_curr_y;
                break;

            default:
                break;
            };

            //show the current location of the player on the screen
            mvaddch(player_curr_y, player_curr_x, player_label);

        };
        
        //hit or pass throught the side borders when reached 
        auto pass_through_wall = [&](const int& wall_side, const int& wall_height, const int& wall_width, const bool& enable)
        {
            //allow to pass throught the walls/borders
            if (enable)
            {
                //mask the previous location of the player with "space"
                mvaddch(player_curr_y, player_curr_x, player_back_footprint);

                //algo to pass throught the borders
                switch (wall_side)
                {

                case KEY_LEFT:
                    player_curr_x = wall_width - 1;
                    break;
                    
                case KEY_RIGHT:
                    player_curr_x = 0;
                    break;

                                        
                case KEY_UP:
                    player_curr_y = wall_height - 1;
                    break;

                                                            
                case KEY_DOWN:
                    player_curr_y = 0;
                    break;

                default:
                    break;
                }
               
                //show the current location of the player on the screen
                mvaddch(player_curr_y, player_curr_x, player_label);
            }
            else
            {
                //hit the wall and wait there
            }
        };
        
        //display player current position after the later has hit a key
        auto displ_player_curr_pos = [&](const int& player_input_loc, const int& wall_height_loc, const int& wall_width_loc)
        {
            switch (player_input_loc)
            {
                //move to the left 
            case KEY_LEFT:
                //when reach left border of the screen pass throught  or hit
                if (player_curr_x == 0)
                {
                    pass_through_wall(KEY_LEFT, wall_height_loc, wall_width_loc, false);
                }
                else
                {
                    mv_to_dir(KEY_LEFT);
                }

                break;
                //move to the right
            case KEY_RIGHT:
                //when reach right border of the screen pass throught  or hit
                if (player_curr_x >= wall_width_loc - 1)
                {
                    pass_through_wall(KEY_RIGHT, wall_height_loc, wall_width_loc, true);
                }
                else
                {
                    mv_to_dir(KEY_RIGHT);
                }

                break;
                //move up
            case KEY_UP:

                //when reach upper border of the screen pass throught  or hit
                if (player_curr_y <= 0)
                {
                    pass_through_wall(KEY_UP, wall_height_loc, wall_width_loc, false);
                }
                else
                {
                    mv_to_dir(KEY_UP);
                }
                break;

                //move down
            case KEY_DOWN:
                //when reach lower border of the screen pass throught  or hit
                if (player_curr_y == wall_height_loc - 1)
                {
                    pass_through_wall(KEY_DOWN, wall_height_loc, wall_width_loc, true);
                }
                else
                {
                    mv_to_dir(KEY_DOWN);
                }
                break;

            default:
                break;
            }
        };

        //close the terminal/screen
        auto close_window = [&]
        {
            getch();
            endwin();
        };


        open_window();

        displ_player_init_pos();

        while (true) 
        {
            //get current screen resolution: height and width
            getmaxyx(stdscr, window_curr_height, window_curr_width);
            //get current player direction: left/right/up/down
            player_input = getch();
            displ_player_curr_pos(player_input, window_curr_height, window_curr_width);

            refresh();
        }

        close_window();

    };
    auto test_basic_7 = []()
    {
        char msg[] = "What is your name: ";
        char str[80];

        initscr();
        addstr(msg);
        getstr(str);
        move(0, 0);
        clrtoeol();
        mvprintw(0, 0, "Welcome to curses %s", str);
        getch();
        endwin();
    };
    auto test_basic_8 = []()
    {
        initscr();

        start_color();
        init_pair(1, COLOR_CYAN, COLOR_BLACK);

        printw("A example string");
        mvchgat(0, 0, -1, A_BLINK, 1, NULL);
        mvprintw(1, 0, "Another example string");
        mvprintw(2, 0, "Yet another example string");
        mvchgat(2, 0, 6, A_BLINK, 1, NULL);

        refresh();
        getch();
        endwin();
    };   
    auto test_basic_9 = []()
    {
        initscr();
        noecho();
        curs_set(FALSE);
        cbreak();

        if (has_colors() == FALSE)
        {
            endwin();
            printf("Your terminal does not support color\n");
            exit(1);
        }
        start_color();
        init_pair(1, COLOR_RED, COLOR_BLACK);
        init_pair(2, COLOR_GREEN, COLOR_BLACK);
        init_pair(3, COLOR_BLUE, COLOR_BLACK);
        init_pair(4, COLOR_YELLOW, COLOR_BLACK);

        attron(COLOR_PAIR(1));
        mvprintw(1, 1, "1. Start");
        attroff(COLOR_PAIR(1));

        attron(COLOR_PAIR(2));
        mvprintw(2, 1, "2. Options");
        attroff(COLOR_PAIR(2));

        attron(COLOR_PAIR(3));
        mvprintw(3, 1, "3. Options");
        attroff(COLOR_PAIR(3));

        attron(COLOR_PAIR(4));
        mvprintw(4, 1, "4. Exit");
        attroff(COLOR_PAIR(4));

        char ch = NULL;
        while (1) {
            ch = getch();
            if (ch == '1') {
                clear();
                mvprintw(0, 0, "Press any key ...");
                break;
            }
            else if (ch == '4') {
                endwin();
                exit(1);
            }
        }

        refresh();
        getch();
        endwin();
    };           
    auto test_basic_10 = []()
    {
        auto create_newwin = [&](int height, int width, int starty, int startx)
        {
            WINDOW* local_win;

            local_win = newwin(height, width, starty, startx);
            wborder(local_win, '|', '|', '-', '-', '+', '+', '+', '+');
            wrefresh(local_win);
            return local_win;
        };

        
        auto destroy_win = [&](WINDOW* local_win)
        {
            wborder(local_win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
            wrefresh(local_win);
            delwin(local_win);
        };

        WINDOW* local_win;
        initscr();
        //mvaddstr(6, 12, "Text will be overwritten by window [press any key]");
        //refresh();
        //scr_dump("savescr.dmp");
        getch();
        local_win = create_newwin(10, 15, 5, 5);

        getch();
        //refresh();
        destroy_win(local_win);
        //getch();
        //mvaddstr(6, 12, "Bring back earlier text by using scr_restore [press any key]");
        //getch();
        //scr_restore("savescr.dmp");
        //refresh();

        getch();
        endwin();
    };    
    auto test_basic_11 = []()
    {

        setlocale(LC_ALL, "");

        //const struct lconv* const currentlocale = localeconv();
        //printf("In the current locale, the default currency symbol is: %s\n",
        //    currentlocale->currency_symbol);
        initscr();

        printw("Upper left corner           "); addch(ACS_ULCORNER); printw("\n");
        printw("Lower left corner           "); addch(ACS_LLCORNER); printw("\n");
        printw("Lower right corner          "); addch(ACS_LRCORNER); printw("\n");
        printw("Tee pointing right          "); addch(ACS_LTEE); printw("\n");
        printw("Tee pointing left           "); addch(ACS_RTEE); printw("\n");
        printw("Tee pointing up             "); addch(ACS_BTEE); printw("\n");
        printw("Tee pointing down           "); addch(ACS_TTEE); printw("\n");
        printw("Horizontal line             "); addch(ACS_HLINE); printw("\n");
        printw("Vertical line               "); addch(ACS_VLINE); printw("\n");
        printw("Diamond                     "); addch(ACS_DIAMOND); printw("\n");
        printw("Checker board (stipple)     "); addch(ACS_CKBOARD); printw("\n");
        printw("Bullet                      "); addch(ACS_BULLET); printw("\n");
        printw("Arrow Pointing Left         "); addch(ACS_LARROW); printw("\n");
        printw("Arrow Pointing Right        "); addch(ACS_RARROW); printw("\n");
        printw("Arrow Pointing Down         "); addch(ACS_DARROW); printw("\n");
        printw("Arrow Pointing Up           "); addch(ACS_UARROW); printw("\n");
        printw("Board of squares            "); addch(ACS_BOARD); printw("\n");
        printw("Solid Square Block          "); addch(ACS_BLOCK); printw("\n");

        refresh();
        getch();
        endwin();
    };
    auto test_basic_12 = []()
    {


        std::vector<std::string> title = {
        "  ___   _     _____ ___________ ",
        " / _ \\ | |   /  __ \\  _  | ___ \\",
        "/ /_\\ \\| |   | /  \\/ | | | |_/ /",
        "|  _  || |   | |   | | | |    / ",
        "| | | || |___| \\__/\\ \\_/ / |\\ \\ ",
        "\\_| |_/\\_____/\\____/\\___/\\_| \\_|"
        };

        std::vector<std::string> adam = {
        "    _____            _____  ",
        "   / __  \\        | |    \\ \\",
        "  / /__ \\ \\       | |    | |",
        " / ______\\ \\      | |    | |",
        "/ /       \\ \\     | |    / /",
        "---        ---      ------  ",
        };

        auto mvprintw_sa = [&](int y, int x, std::vector<std::string> texts)
        {
            int i = 0;
            for (const std::string& text : texts) {
                mvprintw(y + i, x, text.c_str());
                i++;
            }
        };

        /* ascii art */

            initscr();
            start_color();
            init_pair(1, COLOR_GREEN, COLOR_BLACK);

            attron(COLOR_PAIR(1));
            mvprintw_sa(10, 10, adam);
            attroff(COLOR_PAIR(1));

            refresh();
            getch();
            endwin();


    };    
    auto test_basic_13 = []()
    {

        auto mvhline_ws = [&](int y, int x, const char ch, int n)
        {
            std::string line = "";
            line.push_back(ch);

            for (int i = 0; i < n; i++) {
                line = line + " " + ch;
            }
            mvprintw(y, x, line.c_str());
        };

        auto mvvline_ws = [&](int y, int x, const char ch, int n)
        {
            std::string line = "";
            line.push_back(ch);

            for (int i = 0; i < n; i++) {
                if (i % 2 == 0) {
                    mvaddch(y + i, x, ch);
                }
                else {
                    mvaddch(y + i, x, ' ');
                }
            }
        };


        auto mvrectangle = [&](int y, int x, const char ch, int n)
        {
            mvvline(y, x, ch, n);
            mvvline(y, x + n * 2 - 2, ch, n);
            mvhline(y, x + 1, ch, n * 2 - 2);
            mvhline(y + n - 1, x + 1, ch, n * 2 - 2);
        };

        auto mvwrectangle = [&](WINDOW* win, int y, int x, const char ch, int n)
        {
            mvwvline(win, y, x, ch, n);
            mvwvline(win, y, x + n * 2 - 2, ch, n);
            mvwhline(win, y, x + 1, ch, n * 2 - 2);
            mvwhline(win, y + n - 1, x + 1, ch, n * 2 - 2);
        };

        auto mvrectangle_ws = [&](int y, int x, const char ch, int n)
        {
            mvvline(y, x, ch, n);
            mvvline(y, x + n * 2 - 2, ch, n);
            mvhline_ws(y, x + 2, ch, n - 2);
            mvhline_ws(y + n - 1, x + 2, ch, n - 2);
        };

        /* drawing lines,rectangles*/

            initscr();
            start_color();
            init_pair(1, COLOR_GREEN, COLOR_BLACK);

            mvrectangle(1, 1, '#', 5);
            mvrectangle_ws(7, 1, '#', 7);
            mvvline(3, 15, '|', 10);
            mvvline_ws(3, 17, '|', 11);
            mvhline(2, 14, '_', 10);
            mvhline_ws(3, 14, '_', 10);

            refresh();
            getch();
            endwin();



    };    
    
    
    //not working
    auto test_basic_14 = []()
    {


        /*
        BUTTON1_PRESSED          mouse button 1 down
        BUTTON1_RELEASED         mouse button 1 up
        BUTTON1_CLICKED          mouse button 1 clicked
        BUTTON1_DOUBLE_CLICKED   mouse button 1 double clicked
        BUTTON1_TRIPLE_CLICKED   mouse button 1 triple clicked
        BUTTON2_PRESSED          mouse button 2 down
        BUTTON2_RELEASED         mouse button 2 up
        BUTTON2_CLICKED          mouse button 2 clicked
        BUTTON2_DOUBLE_CLICKED   mouse button 2 double clicked
        BUTTON2_TRIPLE_CLICKED   mouse button 2 triple clicked
        BUTTON3_PRESSED          mouse button 3 down
        BUTTON3_RELEASED         mouse button 3 up
        BUTTON3_CLICKED          mouse button 3 clicked
        BUTTON3_DOUBLE_CLICKED   mouse button 3 double clicked
        BUTTON3_TRIPLE_CLICKED   mouse button 3 triple clicked
        BUTTON4_PRESSED          mouse button 4 down
        BUTTON4_RELEASED         mouse button 4 up
        BUTTON4_CLICKED          mouse button 4 clicked
        BUTTON4_DOUBLE_CLICKED   mouse button 4 double clicked
        BUTTON4_TRIPLE_CLICKED   mouse button 4 triple clicked
        BUTTON_SHIFT             shift was down during button state change
        BUTTON_CTRL              control was down during button state change
        BUTTON_ALT               alt was down during button state change
        ALL_MOUSE_EVENTS         report all button state changes
        REPORT_MOUSE_POSITION    report mouse movement
        */

        /* mouse usage */

            MEVENT event;

            int ch = 0;
            initscr();
            raw();
            keypad(stdscr, TRUE);
            noecho();
            mmask_t old;
            mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, &old);


            while (ch != 27)
            {
                ch = getch();
                if (ch == KEY_MOUSE) 
                {
                    auto mouse_state  = getmouse();
                    if (mouse_state == OK)
                    {
                        if (mouse_state & BUTTON1_DOUBLE_CLICKED)
                        {
                            request_mouse_pos();
                            printw("Double click , x: %d y: %d\n", Mouse_status.x, Mouse_status.y);
                            refresh();
                        }
                    }
                }
            }

            refresh();
            endwin();



    };

    //test_basic_1();
    //test_basic_2();
    //test_basic_3();
    //test_basic_4();
    //test_basic_5();
    //test_basic_6();
    //test_basic_7();
    //test_basic_8();
    //test_basic_9();
    //test_basic_10();
    //test_basic_11();
    //test_basic_12();
    //test_basic_13();
    //test_basic_14();
}

void MainMenu::show_settings()
{
    //MenuItem me = { std::string("Field size: ") + std::to_string(Settings::field_size.y) + " rows, " + std::to_string(Settings::field_size.x) + " cols" , Settings::field_size };



    std::vector<MenuItem> settings_menu_items = {   { std::string("Field size: ") + std::to_string(Settings::field_size.y) + " rows, " + std::to_string(Settings::field_size.x) + " cols", Settings::field_size},
                                                    { std::string("Walls: ") + bool_to_str(Settings::enable_walls),  {}},
                                                };



    display_menu(settings_menu_items,
        [&settings_menu_items](menu_item_t p_selected_item)
        {
            switch (p_selected_item)
            {
            
                //field size
            case 0:
                switch (Settings::field_size.y)
                {
                case 18:
                    Settings::field_size = { 30, 80 };
                    break;
                case 25:
                    Settings::field_size = { 10, 20 };
                    break;
                default:
                    Settings::field_size = { 15, 60};
                    break;
                }
                settings_menu_items[0].label = std::string("Field size: ") + std::to_string(Settings::field_size.y) + " rows, " + std::to_string(Settings::field_size.x) + " cols";
                break;
            case 1:
                Settings::enable_walls = !Settings::enable_walls;
                settings_menu_items[1].label = std::string("Walls: ") + bool_to_str(Settings::enable_walls);
                break;
            default:
                break;
            }
        },
        true, "Settings");
}

MainMenu::MainMenu()
{
    initscr();
    cbreak();
    noecho();
    curs_set(0);

    keypad(stdscr, true);
}

MainMenu::~MainMenu()
{
    endwin();
}

void MainMenu::show()
{
    //new_game();
    
    std::vector<MenuItem> main_menu_items = { {
                                            {"New Game", {} },
                                            {"Settings", {} },
                                            {"Exit", {} }
                                            } };

    display_menu(main_menu_items,
        [this](menu_item_t p_selected_item)
        {
            switch (p_selected_item)
            {
                // New Game
            case 0:
                new_game();
                break;
                // Settings
            case 1:
                show_settings();
                break;
            case 2:
                throw GameExit();
            }
        }, false);
        
}

GameUI::GameUI(WINDOW* p_border_win, WINDOW* p_field_win) : m_border_win(p_border_win), m_field_win(p_field_win)
{
    draw_border();
    nodelay(m_field_win, true);
    keypad(m_field_win, true);
}

void GameUI::draw_border()
{
    //box(m_border_win, 0, 0);
    wrefresh(m_border_win);
}

void GameUI::draw_static_elements()
{
    for (int row = 0; row < m_field->m_field_size.y; ++row)
    {
        for (int col = 0; col < m_field->m_field_size.x; ++col)
        //for (int col = 0; col < 40; ++col)
        {
            //mvwaddch(m_field_win, 1, col, '#');
            if (m_field->get({ row, col }) == Object::wall)
            //if (m_field->get({ col, row }) == Object::wall)
            {
                //mvwaddch(m_field_win, row, col, '#');
                mvwaddch(m_field_win, row, col, '#');
            }
        }
    }

    wrefresh(m_field_win);
}

void GameUI::update(int score)
{
    mvwprintw(m_border_win, 0, 2, "Score: %d", score);
    wrefresh(m_border_win);
    update_field();
    wrefresh(m_field_win);
}

void GameUI::update_field()
{
    for (int row = 0; row < m_field->m_field_size.y; ++row)
    {
        for (int col = 0; col < m_field->m_field_size.x; ++col)
        {
            switch (m_field->get({ row, col }))
            {
            case Object::empty:
                mvwaddch(m_field_win, row, col, ' ');
                break;
            case Object::player:
                //mvwaddch(m_field_win, row, col, '*');
                mvwaddch(m_field_win, row, col, '-');
                break;               
            case Object::tail_h:
                //mvwaddch(m_field_win, row, col, '*');
                mvwaddch(m_field_win, row, col, '-');
                break;              
            case Object::tail_v:
                //mvwaddch(m_field_win, row, col, '*');
                mvwaddch(m_field_win, row, col, '|');
                break;   
            case Object::head_right:
                //mvwaddch(m_field_win, row, col, '*');
                mvwaddch(m_field_win, row, col, '>');
                break;            
            case Object::head_left:
                //mvwaddch(m_field_win, row, col, '*');
                mvwaddch(m_field_win, row, col, '<');
                break;            
            case Object::head_up:
                //mvwaddch(m_field_win, row, col, '*');
                mvwaddch(m_field_win, row, col, '^');
                break;            
            case Object::head_down:
                //mvwaddch(m_field_win, row, col, '*');
                mvwaddch(m_field_win, row, col, 'v');
                break;
            case Object::food:
                mvwaddch(m_field_win, row, col, '$');
                break;
            default:
                break;
            }
        }
    }
}

Facing GameUI::get_input()
{

    noecho();
    keypad(m_field_win, TRUE);
    //int input = wgetch(m_field_win);

    //switch (input)
    //{
    //case KEY_UP:
    //    return Facing::up;
    //case KEY_RIGHT:
    //    return Facing::right;
    //case KEY_DOWN:
    //    return Facing::down;
    //case KEY_LEFT:
    //    return Facing::left;
    //case 'q':
    //case 27:
    //    throw GameEndQuit();
    //    break;
    //}

    //return Facing::null;    
    
    int ch;
    nodelay(m_field_win, TRUE);
    for (;;)
    {
        if ((ch = wgetch(m_field_win)) == ERR)
        {
            break;
            /* user hasn't responded
             ...
            */
        }
        else
        {
            switch (ch)
            {
            case KEY_UP:
                return Facing::up;
            case KEY_RIGHT:
                return Facing::right;
            case KEY_DOWN:
                return Facing::down;
            case KEY_LEFT:
                return Facing::left;
            case 'q':
            case 27:
                throw GameEndQuit();
                break;
            };
            break;
        }
    }
    return Facing::null;
}

menu_item_t UIUtils::dialogbox(std::string p_text, std::vector<std::string> p_buttons)
{
    // if COLS / 4 < min_width(the width so that all elements would fit) -> width = COLS - 4, else width = COLS / 4
    int width = COLS / 4 < [&p_text, &p_buttons]() -> int
    {
        int min_width = 0;
        for (std::string button : p_buttons)
        {
            min_width += button.length() + 2;
        }
        min_width = min_width > (int)p_text.length() ? min_width : p_text.length();
        return min_width + 10;
    } () ? COLS - 10 : COLS / 4;

    WINDOW* win = newwin(7, width, (LINES - 7) / 2, (COLS - (width)) / 2);
    keypad(win, true);

    box(win, 0, 0);
    mvwprintw(win, 2, (win->_maxx - p_text.length()) / 2, p_text.c_str());
    wrefresh(win);

    menu_item_t selected_item = 0;
    while (true)
    {
        for (std::size_t i = 0; i < p_buttons.size(); ++i)
        {
            // x = (total width of the window / (amount of buttons + 1)) * (current button + 1) - (length of the text of the button / 2)
            mvwprintw(win,
                5,
                (win->_maxx / (p_buttons.size() + 1)) * (i + 1) - (p_buttons[i].length() / 2),
                p_buttons[i].c_str());
        }

        mvwchgat(win, 5, (win->_maxx / (p_buttons.size() + 1)) * (selected_item + 1) - (p_buttons[selected_item].length() / 2), p_buttons[selected_item].length(), A_STANDOUT, 0, NULL);

        switch (wgetch(win))
        {
        case KEY_LEFT:
            selected_item = selected_item != 0 ? selected_item - 1 : p_buttons.size() - 1;
            break;
        case KEY_RIGHT:
            selected_item = selected_item != (int)p_buttons.size() - 1 ? selected_item + 1 : 0;
            break;
            // Enter
        case '\n':
            werase(win);
            wrefresh(win);
            delwin(win);
            return selected_item;
        }
    }

    throw std::logic_error("Out of the infinite while loop");
}