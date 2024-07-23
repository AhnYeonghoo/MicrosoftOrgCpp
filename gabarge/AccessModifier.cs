using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AccessModifier
{
    class WaterHeater
    {
        protected int temperature;

        public void SetTemperature(int temperature)
        {
            if (temperature < -5 || temperature > 42)
            {
                throw new Exception("Out of temperature range");
            }
            this.temperature = temperature;
        }

        internal void TurnOnWater()
        {
            Console.WriteLine($"Turn On Water: {temperature}");
        }
    }
    internal class AccessModifier
    {
        static void MaimAccessModifier()
        {
            try
            {
                WaterHeater heater = new WaterHeater();
                heater.SetTemperature(20);
                heater.TurnOnWater();

                heater.SetTemperature(-2);
                heater.TurnOnWater();

                heater.SetTemperature(50);
                heater.TurnOnWater();
            }
            catch (Exception e)
            {
                Console.WriteLine(e.Message);
            }
        }
    }
}
