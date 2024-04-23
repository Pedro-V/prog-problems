using System.Collections.Generic;

public record FacialFeatures(string EyeColor, decimal PhiltrumWidth);
public record Identity(string Email, FacialFeatures FacialFeatures);

public class Authenticator
{
    private HashSet<Identity> identities = new();
    private Identity admin = new("admin@exerc.ism", new FacialFeatures("green", 0.9m));

    public static bool AreSameFace(FacialFeatures faceA, FacialFeatures faceB) => faceA.Equals(faceB);
    
    public bool IsAdmin(Identity identity) => identity.Equals(admin);

    public bool Register(Identity identity) => identities.Add(identity);

    public bool IsRegistered(Identity identity) => identities.Contains(identity);

    public static bool AreSameObject(object identityA, object identityB) =>  identityA == identityB;
}
