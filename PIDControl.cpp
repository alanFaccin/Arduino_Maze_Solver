#include "PIDControl.h"
#include "Robot.h"

PIDControl::PIDControl():m_last_error(0),m_integral(0),m_Kp(40),m_Ki(65),m_Kd(57)
{
}

void PIDControl::reset()
{
  m_last_error=0;
  m_integral=0;
  m_error=0;
}

int PIDControl::move(int speedRobot)
{
    int proportional = m_error/35; //metade do valor maximo
    int derivative = (m_error - m_last_error);
    derivative=constrain(derivative, -2000, 2000);
    m_integral += m_error;
    m_integral=constrain(m_integral, -200, 200);
    m_last_error = m_error;
    return m_Kp*proportional/10*speedRobot/500+(m_Ki*m_integral)/600+(m_Kd*derivative)/100;
}
