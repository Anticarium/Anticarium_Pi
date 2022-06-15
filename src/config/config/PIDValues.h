#pragma once

class PIDValues {
  public:
    int getP() const;
    void setP(int p);

    int getI() const;
    void setI(int i);

    int getD() const;
    void setD(int d);

  private:
    int p = 0;
    int i = 0;
    int d = 0;
};
