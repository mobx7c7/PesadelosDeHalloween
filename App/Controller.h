/***********************************************************************
    Autor               : Marcelo de Oliveira Bittencourt
    Data de criação     : 2015-03-13
***********************************************************************/
#ifndef CONTROLLER_H
#define CONTROLLER_H

typedef void (*MouseMovedFunc)(int, int);
typedef void (*MouseDraggedFunc)(int, int, int);
typedef void (*MousePressedFunc)(int, int, int);
typedef void (*MouseReleasedFunc)(int, int, int);
typedef void (*KeyPressedFunc)(int);
typedef void (*KeyReleasedFunc)(int);
typedef void (*KeyRepeatedFunc)(int);

class KeyboardController
{
	private:
		static KeyboardController* instance;
	protected:
		KeyboardController();
		~KeyboardController();
	public:
		static KeyboardController*  getInstance();
		static void                 destroyInstance();

        virtual bool                isKeyPressed(unsigned key) const = 0;
        virtual bool                isKeyRepeated(unsigned key) const = 0;
        virtual void                poolEvents() = 0;

        virtual void                registerKeyReleasedFunc(KeyReleasedFunc) = 0;
        virtual void                registerKeyPressedFunc(KeyPressedFunc) = 0;
};

class MouseController
{
    private:
		static MouseController* instance;
	public:
		MouseController();
		~MouseController();
		static MouseController* getInstance();
		static void             destroyInstance();
        virtual bool            isButtonPressed(unsigned button) const = 0;
        virtual double          getDX() const = 0;
        virtual double          getDY() const = 0;
        virtual double          getX() const = 0;
        virtual double          getY() const = 0;
        virtual void            poolEvents() = 0;

        virtual void            registerMouseMovedFunc(MouseMovedFunc) = 0;
        virtual void            registerMouseDraggedFunc(MouseDraggedFunc) = 0;
        virtual void            registerMouseReleasedFunc(MouseReleasedFunc) = 0;
        virtual void            registerMousePressedFunc(MousePressedFunc) = 0;
};
#endif // CONTROLLER_H
