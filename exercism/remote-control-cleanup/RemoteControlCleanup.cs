  public class RemoteControlCar
{
    public string CurrentSponsor { get; private set; }
    public CTelemetry Telemetry;
    private Speed currentSpeed;
    
    public RemoteControlCar() => Telemetry = new RemoteControlCar.CTelemetry(this);

    public string GetSpeed() => currentSpeed.ToString();

    private void SetSponsor(string sponsorName) => CurrentSponsor = sponsorName;

    private void SetSpeed(Speed speed) => currentSpeed = speed;

    public class CTelemetry
    {
        private readonly RemoteControlCar car;

        public CTelemetry(RemoteControlCar car) => this.car = car;
    
        public void Calibrate() {}
        
        public bool SelfTest() => true;
    
        public void ShowSponsor(string sponsorName) => _car.SetSponsor(sponsorName);
    
        public void SetSpeed(decimal amount, string unitsString)
        {
            SpeedUnits speedUnits = unitsString == "cps" ? SpeedUnits.CentimetersPerSecond : SpeedUnits.MetersPerSecond;
            _car.SetSpeed(new Speed(amount, speedUnits));
        }
    }

    enum SpeedUnits { MetersPerSecond, CentimetersPerSecond }

    record struct Speed(decimal Amount, SpeedUnits SpeedUnits)
    {
        public override string ToString()
        {
            string units = SpeedUnits == SpeedUnits.CentimetersPerSecond ? "centimeters" : "meters";
            return $"{Amount} {units} per second";
        }
    }
}
