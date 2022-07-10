#include "core.h"
#include <QDebug>

Core::Core()
{
    p1x = 1;
    p1y = 1;
    p2x = 18;
    p2y = 13;
    r1x = 18;
    r1y = 1;
    r2x = 1;
    r2y = 13;
}

void Core::UpdateLocation(int id, int x, int y)
{
    if (id == 1)
    {
        p1x = x;
        p1y = y;
    }
    else if (id == 2)
    {
        p2x = x;
        p2y = y;
    }
    else if (id == 3)
    {
        r1x = x;
        r1y = y;
    }
    else
    {
        r2x = x;
        r2y = y;
    }
}

int Core::checkX(int id)
{
    if (id == 1)
        return p1x;
    else if (id == 2)
        return p2x;
    else if (id == 3)
        return r1x;
    else
        return r2x;
}

int Core::checkY(int id)
{
    if (id == 1)
        return p1y;
    else if (id == 2)
        return p2y;
    else if (id == 3)
        return r1y;
    else
        return r2y;
}

bool Core::current(int x, int y)
{
    if (this->m_data[x][y] == 0 || this->m_data[x][y] == 6 || this->m_data[x][y] == 11)
        return true;
    else
        return false;
}

bool Core::dangerous(int x, int y)
{
    if (this->m_data[x][y] == 11 || this->m_data[x][y] == -1 || this->m_data[x][y] == 6)
        return true;
    else
        return false;
}

bool Core::breakable(int x, int y)
{
    if (this->m_data[x][y] == 0 || this->m_data[x][y] == 3 || this->m_data[x][y] == 4 || this->m_data[x][y] == 6 || this->m_data[x][y] == 11)
        return true;
    else
        return false;
}

bool Core::fireable(int x, int y)
{
    if (this->m_data[x][y] == 3 || this->m_data[x][y] == 4)
        return true;
    else
        return false;
}

bool Core::eatable(int x, int y)
{
    if (this->m_data[x][y] == 0
            && (this->p_data[x][y] == 7 || this->p_data[x][y] == 8 ||this->p_data[x][y] == 9 ||this->p_data[x][y] == 10))
        return true;
    else
        return false;
}

bool Core::SafePassage(int x, int y)
{
    if (current(x, y) && !dangerous(x, y))
        return true;
    else
        return false;
}

void Core::onAttach()
{
}

void Core::onUpdate(float deltaTime)
{
    for (int i = 0; i < 15; i++)
        for (int j = 0; j < 20; j++)
        {
            qDebug()<<"*****"<<m_data[i][0]<<" "<<m_data[i][1]<<" "<<m_data[i][2]<<" "<<m_data[i][3]<<" "<<m_data[i][4]<<" "<<m_data[i][5]<<" "<<m_data[i][6]<<" "<<m_data[i][7]<<" "<<m_data[i][8]<<" "<<m_data[i][9]<<" "<<m_data[i][10]<<" "<<m_data[i][11]<<" "<<m_data[i][12]<<" "<<m_data[i][13]<<" "<<m_data[i][14]<<" "<<m_data[i][15]<<" "<<m_data[i][16]<<" "<<m_data[i][17]<<" "<<m_data[i][18]<<" "<<m_data[i][19]<<" ";
        }
}
