using System;

class RemoteControlCar
{
    private int _drivenDistance;
    private int _battery = 100;
    
    public static RemoteControlCar Buy() => new RemoteControlCar();

    public string DistanceDisplay() => $"Driven {_drivenDistance} meters";

    public string BatteryDisplay() => 
        _battery == 0 ? "Battery empty" : $"Battery at {_battery}%";

    public void Drive()
    {
        if (_battery == 0) return;
        
        _drivenDistance += 20;
        _battery -= 1;
    }
}

