using System;

class RemoteControlCar
{
    private int _distanceDriven;
    private int _battery = 100;
    private int _speed;
    private int _batteryDrain;

    public RemoteControlCar(int speed, int batteryDrain)
    {
        _speed = speed;
        _batteryDrain = batteryDrain;
    }
    public bool BatteryDrained() => _battery < _batteryDrain;

    public int DistanceDriven() => _distanceDriven;

    public void Drive()
    {
        if (BatteryDrained()) return;
        
        _distanceDriven += _speed;
        _battery -= _batteryDrain;
    }

    public static RemoteControlCar Nitro() =>
        new RemoteControlCar(speed: 50, batteryDrain: 4);
}

class RaceTrack
{
    private int _distance;

    public RaceTrack(int distance)
    {
        _distance = distance;
    }

    public bool TryFinishTrack(RemoteControlCar car)
    {
        while (!car.BatteryDrained()) {
            car.Drive();
        }
        return car.DistanceDriven() >= _distance;
    }
}
