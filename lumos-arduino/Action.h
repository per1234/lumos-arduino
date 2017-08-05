#ifndef _ACTION_H_
#define _ACTION_H_

#include "Patterns.h"

// A generic superclass for actions.
class Action {
  private:
    long nextUpdateMS = 0;

  protected:
    long getNextUpdateMS() { return nextUpdateMS; }
    void setNextUpdateMS(long val) { nextUpdateMS = val; }

    // Paint will be called by loop() when its time to make a change to the lights.
    // Implementations should set pixel colors but should not call strip.show().
    // Implementations mmust update nextUpdateMS to indicate when paint() should be called again.
    virtual void paint() = 0;
  public:
    // Action runners should call loop periodically.
    virtual void loop();
};

class NullAction : public Action {
  private:
    void paint() { }
};

// An Action that alternates between two colors with the given period.
class Blink : public Action {
  private:
    Pixels const pixels;
    int const periodMS;
    int const firstPixel;
    int const lastPixel;
    Color colors[2];
    int colorIndex;

    void paint();

  public:
    Blink(Pixels pixels, int periodMS, int firstPixel, int lastPixel, Color c1, Color c2);
    void setup();
};

// An action that rotates or shifts lights to the left or right.
class Rotate : public Action {
  private:
    int firstPixel;
    int lastPixel;
    int const pixelsPerSecond;
    Direction const op;
    
    void paint();

  public:
    Rotate(int pixelsPerSecond, Direction op) : Rotate(0, strip.numPixels(), pixelsPerSecond, op) { }
    Rotate(int firstPixel, int lastPixel, int pixelsPerSecond, Direction op)
        : firstPixel(firstPixel), lastPixel(lastPixel), pixelsPerSecond(pixelsPerSecond), op(op) { }
};

class Flicker : public Action {
  private:
    int firstPixel;
    int lastPixel;
    Color color;

    void paint();
  
  public:
    Flicker(int firstPixel, int lastPixel, Color color) : firstPixel(firstPixel), lastPixel(lastPixel), color(color) { }
    Flicker(int pixel, Color color) : Flicker(pixel, pixel + 1, color) { }
    Flicker(Color color) : Flicker(0, strip.numPixels(), color) { }
    void setup();
};

// DualAction
class DualAction : public Action {
  private:
    Action * const action1;
    Action * const action2;
  
    void paint() {}
    
  public:
    DualAction(Action *a1, Action *a2) : action1(a1), action2(a2) { }
    void loop();
};

// TripleAction
class TripleAction : public Action {
  private:
    Action * const action1;
    Action * const action2;
    Action * const action3;

    void paint() {}
    
  public:
    TripleAction(Action *a1, Action *a2, Action *a3) : action1(a1), action2(a2), action3(a3) { }
    void loop();
};

#endif // _ACTION_H_
