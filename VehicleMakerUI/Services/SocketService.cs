using System.Net.Sockets;
using System.Text;
using System.Text.Json;
using VehicleMakerUI.Models;

public static class SocketService
{
    public static string SendConfiguration(VehicleConfiguration config, string testMode)
    {
        var payload = new
        {
            Test = testMode,
            Data = config
        };

        string json = JsonSerializer.Serialize(payload);
        byte[] data = Encoding.UTF8.GetBytes(json);

        using TcpClient client = new TcpClient("127.0.0.1", 8080);
        using NetworkStream stream = client.GetStream();

        stream.Write(data, 0, data.Length);

        byte[] buffer = new byte[1024];
        int bytes = stream.Read(buffer, 0, buffer.Length);
        return Encoding.UTF8.GetString(buffer, 0, bytes);
    }
}
