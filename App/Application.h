/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2015-03-16
***********************************************************************/
#ifndef APPLICATION_H
#define APPLICATION_H

class App
{
public:
    virtual void setup();
    virtual void update();
    virtual void draw();
	virtual void keyPressed(int key);
    virtual void keyReleased(int key);
    virtual void mouseMoved(int x, int y);
    virtual void mouseDragged(int x, int y, int button);
    virtual void mousePressed(int x, int y, int button);
    virtual void mouseReleased(int x, int y, int button);
    virtual void windowResized(int w, int h);
};

#endif // APPLICATION_H
