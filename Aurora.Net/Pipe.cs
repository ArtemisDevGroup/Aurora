using Aurora.Net.CLI;
using Aurora.Net.Exceptions;
using System.Text;
using System.Runtime.InteropServices;

namespace Aurora.Net
{
    public enum PipeOpenMode
    {
        Inbound = 0,
        Outbound = 1,
        Duplex = 2
    }

    public enum PipeModeFlags
    {

    }

    public interface INamedPipeBase
    {
        public PipeOpenMode OpenMode { get; }
        public string PipeName { get; }
        public IntPtr PipeHandle { get; set; }

        public abstract void Create();

        public void Read(byte[] data)
        {
            if (!PipeHelper.ReadPipe(PipeHandle, data)) throw new WindowsApiException("ReadFile");
        }
        public T Read<T>() where T : struct
        {
            byte[] data = new byte[Marshal.SizeOf<T>()];
            Read(data);
            GCHandle handle = GCHandle.Alloc(data, GCHandleType.Pinned);
            T retValue = Marshal.PtrToStructure<T>(handle.AddrOfPinnedObject());
            handle.Free();
            return retValue;

        }
        public string ReadString(Encoding encoding)
        {
            byte[] data = new byte[1024];
            Read(data);
            return encoding.GetString(data);
        }

        public void Write(byte[] data)
        {
            if (!PipeHelper.WritePipe(PipeHandle, data)) throw new WindowsApiException("WriteFile");
        }
        public void Write(sbyte data)
        {
            Write(new byte[1] { Convert.ToByte(data) });
        }
        public void Write(short data)
        {
            byte[] byteData = BitConverter.GetBytes(data);
            Write(byteData);
        }
        public void Write(int data)
        {
            byte[] byteData = BitConverter.GetBytes(data);
            Write(byteData);
        }
        public void Write(long data)
        {
            byte[] byteData = BitConverter.GetBytes(data);
            Write(byteData);
        }
        public void Write(byte data)
        {
            Write(new byte[1] { data });
        }
        public void Write(ushort data)
        {
            byte[] byteData = BitConverter.GetBytes(data);
            Write(byteData);
        }
        public void Write(uint data)
        {
            byte[] byteData = BitConverter.GetBytes(data);
            Write(byteData);
        }
        public void Write(ulong data)
        {
            byte[] byteData = BitConverter.GetBytes(data);
            Write(byteData);
        }
    }

    public class NamedPipeServer : INamedPipeBase
    {
        public PipeOpenMode OpenMode { get; }
        public PipeModeFlags PipeMode { get; }
        public string PipeName { get; }
        public IntPtr PipeHandle { get; set; }

        public NamedPipeServer(string name, PipeOpenMode openMode, PipeModeFlags pipeMode)
        {
            OpenMode = openMode;
            PipeMode = pipeMode;

            string nameStart = "\\\\.\\pipe\\";
            for (int i = 0; i < nameStart.Length; i++)
                if (name[i] != nameStart[i])
                {
                    PipeName = nameStart + name;
                    return;
                }

            PipeName = name;
        }

        public void Create()
        {
            PipeHandle = PipeHelper.CreatePipe(PipeName, (uint)OpenMode, (uint)PipeMode);
            if (PipeHandle == IntPtr.Zero) throw new WindowsApiException("CreateNamedPipeW");
        }
    }

    public class NamedPipeClient : INamedPipeBase
    {
        public PipeOpenMode OpenMode { get; }
        public string PipeName { get; }
        public IntPtr PipeHandle { get; set; }

        public NamedPipeClient(string pipeName, PipeOpenMode openMode)
        {
            PipeName = pipeName;
            OpenMode = openMode;
        }

        public void Create()
        {
            PipeHandle = PipeHelper.OpenPipe(PipeName, (uint)OpenMode);
            if (PipeHandle == IntPtr.Zero) throw new WindowsApiException("CreateFileW");
        }
    }
}
