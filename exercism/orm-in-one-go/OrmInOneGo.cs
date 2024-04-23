using System;

public class Orm
{
    private Database database;

    public Orm(Database database)
    {
        this.database = database;
    }

    public void Write(string data)
    {
        using (var db = database)
        {
            db.BeginTransaction();
            db.Write(data);
            db.EndTransaction();
        }
    }

    public bool WriteSafely(string data)
    {
        try {
            Write(data);
            return true;
        } catch (Exception) {
            return false;
        }
    }
}
