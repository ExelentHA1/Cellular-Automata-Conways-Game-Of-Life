/*
April 9, 2026

Cellular Automata

Conway's Game of Life

Rules:
    * any live cell with fewer than two live neighbors die (underpopulation)
    * any live cell with with 2 or 3 live neigbors lives on the next generation
    * any live cell with with more than three neighbors die (overpopulation)
    * any dead cell with exacly three neighbors live (reproduction)
*/

#include <iostream>
#include <curses.h>
#include <vector>

#include <random>

struct cells
{
    int state = 0; // 1 - dead, 0 - live
    bool nextS = 0; // status next state
};

int isValidCell(int x, int y, int w, int h)
{
    if(x >= 0 && y >= 0 && x <= w && y <= h)
        return 1;
    return 0;
}

int countNeighbors(std::vector<std::vector<cells>> &arr, int x, int y)
{
    int count = 0;
    int w = arr[0].size();
    int h = arr.size();

    // check adjacent cell
    if(isValidCell(x-1, y-1, w, h)) // upper left
        if(arr[y-1][x-1].state == 1)
            count++;
    if(isValidCell(x, y-1, w, h)) // upper
        if(arr[y-1][x].state == 1)
            count++;
    if(isValidCell(x+1, y-1, w, h)) // upper right
        if(arr[y-1][x+1].state == 1)
            count++;
    if(isValidCell(x-1, y, w, h)) // left
        if(arr[y][x-1].state == 1)
            count++;
    if(isValidCell(x+1, y, w, h)) // right
        if(arr[y][x+1].state == 1)
            count++;
    if(isValidCell(x-1, y+1, w, h)) // lower left
        if(arr[y+1][x-1].nextS == 1)
            count++;
    if(isValidCell(x, y+1, w, h)) // lower 
        if(arr[y+1][x].state == 1)
            count++;
    if(isValidCell(x+1, y+1, w, h)) // lower right
        if(arr[y+1][x+1].state == 1)
            count++;
    return count;
}

cells initcells()
{
    cells c;
    c.state = std::rand() % 2;
    c.nextS = 0;
    return c;
}

void renderCells(std::vector<std::vector<cells>> arr, int height, int width)
{
    for (int y = 0; y < height; y++)
    {
        for(int x = 0; x < width; x++)
        {
            if(arr[y][x].state == 1)
            {
                mvprintw(y, x, "#");
            }
        }
    }
}

void evalCells(std::vector<std::vector<cells>> &arr) // update next state
{
    int w = arr[0].size()-1;
    int h = arr.size()-1;
    for (int y = 0; y < h; y++)
    {
        for (int x = 0; x < w; x++)
        {
            int count = countNeighbors(arr, x, y);
            if(arr[y][x].state == 1)
            {
                if(count >= 2 && count <= 3) // any live cell with fewer than two live neighbors die (underpopulation)
                {    
                    arr[y][x].nextS = 1;
                }// any live cell with with 2 or 3 live neigbors lives on the next generation
                else // any live cell with with more than three neighbors die (overpopulation)
                {
                    arr[y][x].nextS = 0;
                }         
            }
            else
            {
                if(count == 3) // any dead cell with exacly three neighbors live (reproduction)
                    arr[y][x].nextS = 1;
            }
            
        }
    }
}

void updateCells(std::vector<std::vector<cells>> &arr) // update curr state
{
    int w = arr[0].size();
    int h = arr.size();
    for (int y = 0; y < h; y++)
    {
        for (int x = 0; x < w; x++)
        {
            arr[y][x].state = arr[y][x].nextS;
        }
    }
}

void getTermDimentions(int *x, int *y); // helper functions

int main() {
    // Initialize the ncurses screen
    initscr();
    
    // Optional settings
    cbreak();            // Disable line buffering

    nodelay(stdscr, TRUE);
    noecho();            // Don't echo key presses
    curs_set(0); // hide cursor

    int ch = 0;
    int width, height;
    getTermDimentions(&width, &height);
    
    std::vector<std::vector<cells>> arr = {};
    // arr[y][x]
    for (int y = 0; y < height; y++)
    {
        std::vector<cells> i = {};
        arr.push_back(i);
        for(int x = 0; x < width; x++)
        {
            cells c;
            arr[y].push_back(initcells());
        }
    }
    int gen = 0;
    float del = 0;
    float dt = 0;
    while(true)
    {
        dt+=0.0016;
        ch = getch();
        if(ch == 'q')
            break;
        clear();
        if(dt > del)
        {
            gen++;
            del = dt+(0.0016*60*0);
            evalCells(arr);
            updateCells(arr);
        }
        
        renderCells(arr, height, width);
        
        mvprintw(height-1, 0, "|window size\tx: %d y: %d, deltaT: %.02f Generation: %d|", width, height, dt, gen);

        refresh();
        napms(16);
    }
    // End ncurses mode
    endwin();
}

void getTermDimentions(int *x, int *y)
{
    *x = getmaxx(stdscr);
    *y = getmaxy(stdscr);
}