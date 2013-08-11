/*
========================================================================

	Handles error and standard system output 
	outputs to several different log files

========================================================================
*/

package Managers;

import java.io.File;
import java.io.PrintStream;

public class LogManager {
    
    // LOG_APP    - Kernel-level messages and other misc messages
    // LOG_CLIENT - video, sound, and player end tasks
    // LOG_SERVER - connections being opened and closed, and games being started and stopped, and ai/physics messages
    // LOG_USER   - used to display the errors to a user in a dialog box
    
    public static enum LOG { APP, CLIENT, SERVER, USER }
    private static boolean debug = true; // change this before release
    
    protected PrintStream appLog;
    protected PrintStream clientLog;
    protected PrintStream serverLog;
    
    private static LogManager instance = null;  //the only instance
    
    public void StartUp() {
         try {
            appLog    = new PrintStream("applog.txt");
            clientLog = new PrintStream("clntlog.txt");
            serverLog = new PrintStream("srvrlog.txt");
        } catch (Exception e) {
            System.out.println("ErrorLog::init: " + e);
        }
    }
    
    public void ShutDown() {
        appLog.close();
        clientLog.close();
        serverLog.close();
    }
    
    public int Write( LOG target, String format, Object... variableArguments ) {
        format = System.currentTimeMillis() + ": " + format + "\n";
        
        switch (target) {
            case APP:
                appLog.printf(format, variableArguments);
                break;
            case CLIENT:
                clientLog.printf(format, variableArguments);
                break;
            case SERVER:
                serverLog.printf(format, variableArguments);
                break;
            case USER:
                //System.out.printf(format, variableArguments);
                break;
            default:
                break;
        }
        
        if(debug){
            System.out.printf(format, variableArguments);
        }
        
        return 1; // technically not correct...
    }
    
    protected LogManager() {
        // do nothing
    }
    
    /**
     * Obtain the GameKernel singleton instance
     * @return
     */
    public static LogManager GetInstance(){
        if(instance == null){
            instance = new LogManager();
        }
        return instance;
    }
    
}
