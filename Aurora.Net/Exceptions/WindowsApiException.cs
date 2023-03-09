namespace Aurora.Net.Exceptions
{
    public class WindowsApiException : Exception
    {
        public string WindowsFunction { get; private set; }
        public string WindowsMessage { get; set; }
        public uint WindowsCode { get; set; }

        public WindowsApiException(string functionName) : base("A Windows API function has failed.")
        {
            WindowsFunction = functionName;
            WindowsCode = CLI.GetLastErrorHelper.GetLastError();
            WindowsMessage = CLI.GetLastErrorHelper.FormatSystemErrorCode(WindowsCode);
        }
    }
}
