/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package gui;

import com.fazecast.jSerialComm.SerialPort;
import java.io.IOException;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author Kishk
 */
public class RaspberryConnect {
    SerialPort Sp;
    Thread SerialReadThread;
    byte[] TempData;
    RaspberryConnect()
    {
        TempData = new byte[1];
        Sp = SerialPort.getCommPort("/dev/ttyUSB0");  
        Sp.openPort();
        if(Sp.isOpen())
        {
            System.out.println("Connected!");
        }
        else
        {
            System.out.println("Not Connected!!");
        }
    }

    public byte RaspberryReadData()
    {
       
        TempData[0]=-1;
        Sp.readBytes(TempData, 1);
        try {
            byte Dummy = (byte) Sp.getInputStream().read();
                    
        } catch (IOException ex) {
//            Logger.getLogger(RaspberryConnect.class.getName()).log(Level.SEVERE, null, ex);
        }

        if(TempData[0]!= -1)
        {
            System.out.println("Incoming Input: " + TempData[0]);
        }
        else
        {
            TempData[0] = -1;
        }
        return TempData[0];
    }
    
    
    
   
    }

//    public void connectionTask() 
//    {
//        Runnable RecieveRunnable = ()->{
//                while(true)
//                {
//                    if(Sp.getInputStream() != null)
//                    {
//                        try {
//                            System.out.print((char)Sp.getInputStream().read());
//                            try {
//                                SerialReadThread.sleep(10);
//                            } catch (InterruptedException ex) {
////                                Logger.getLogger(RaspiConnection.class.getName()).log(Level.SEVERE, null, ex);
//                            }
//                        } catch (IOException ex) {
////                            Logger.getLogger(RaspiTest.class.getName()).log(Level.SEVERE, null, ex);
//                        }
//                    }
//                }
//        };
//        SerialReadThread = new Thread(RecieveRunnable);
//        SerialReadThread.start();
//    }


