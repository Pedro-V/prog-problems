using System;

public class RemoteControlCar
{
    private int batteryPercentage = 100;
    private int distanceDrivenInMeters = 0;
    private string[] sponsors = new string[0];
    private int latestSerialNum = 0;

    public void Drive()
    {
        if (batteryPercentage > 0)
        {
            batteryPercentage -= 10;
            distanceDrivenInMeters += 2;
        }
    }

    public void SetSponsors(params string[] sponsors)
    {
        this.sponsors = sponsors;
    }

    public string DisplaySponsor(int sponsorNum) => sponsors[sponsorNum];

    public bool GetTelemetryData(ref int serialNum,
        out int batteryPercentage, out int distanceDrivenInMeters)
    {
        bool success = true;
        if (serialNum < latestSerialNum) {
            serialNum = latestSerialNum;
            this.batteryPercentage = -1;
            this.distanceDrivenInMeters = -1;
            success = false;
        } else {
            latestSerialNum = serialNum;
        }
        batteryPercentage = this.batteryPercentage;
        distanceDrivenInMeters = this.distanceDrivenInMeters;
        return success;
    }

    public static RemoteControlCar Buy() => new RemoteControlCar();
}

public class TelemetryClient
{
    private RemoteControlCar car;

    public TelemetryClient(RemoteControlCar car)
    {
        this.car = car;
    }

    public string GetBatteryUsagePerMeter(int serialNum)
    {
        bool success = car.GetTelemetryData(ref serialNum, out var batteryPercentage, out var distanceDriven);
        if (!success || distanceDriven == 0) return "no data";
        int usage = (100 - batteryPercentage) / distanceDriven;
        return $"usage-per-meter={usage}";
    }
}

