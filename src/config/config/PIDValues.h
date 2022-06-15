#pragma once

class PIDValues {
  public:
    double getP() const;
    void setP(double p);

    double getI() const;
    void setI(double i);

    double getD() const;
    void setD(double d);

  private:
    double p = 0;
    double i = 0;
    double d = 0;
};
