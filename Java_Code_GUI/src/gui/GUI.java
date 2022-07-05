/** ******************************************************************
 * Project: Motor Controller
 * Description:
 *
 *
 *
 * Version 1.0
 *
 * @authors Ahmed Kishk
            Sarah Yasser
 *
 *******************************************************************
 */
package gui;

import eu.hansolo.medusa.Gauge;
import eu.hansolo.medusa.skins.SimpleDigitalSkin;
import java.io.FileNotFoundException;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.logging.Level;
import java.util.logging.Logger;
import javafx.animation.AnimationTimer;
import javafx.application.Application;
import javafx.application.Platform;
import javafx.event.EventHandler;
import javafx.scene.Scene;
import javafx.scene.control.Label;
import javafx.scene.effect.Glow;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.StackPane;
import javafx.scene.paint.Color;
import javafx.scene.text.Font;
import javafx.scene.text.Text;
import javafx.stage.Stage;
import javafx.stage.StageStyle;
import javafx.stage.WindowEvent;

public class GUI extends Application {

    /**
     * *************************************************************
     */
    /**
     * ****************** Variables Declarations *******************
     */
    /**
     * *************************************************************
     */
    /**
     * **************************
     */
    /*      UART Variable        */
    /**
     * **************************
     */
    byte RecievedData;
    char State = 0;
    byte US_FL = 100;
    byte US_FC = 100;
    byte US_FR = 100;
    byte US_BL = 100;
    byte US_BC = 100;
    byte US_BR = 100;
    volatile byte Motor_Rpm;
    byte DesiredData;
    int wegz;

    /**
     * **************************
     */
    /* Flags & Numeric Variables */
    /**
     * **************************
     */
    int speedRPM;
    int speedKM;
    double warningSignOpacity = 0.5;

    /**
     * **************************
     */
    /**
     * ***** Time and Date ******
     */
    /**
     * **************************
     */
    DateTimeFormatter dtf;
    DateTimeFormatter dtf2;
    LocalDateTime T2;
    LocalDateTime T1;

    /**
     * **************************
     */
    /**
     * *** Car Sensors Flags ****
     */
    /**
     * **************************
     */
    /**
     * ***** Front Sensors ******
     */
    // Front Left
    float greenSignOpacityFL = 1;
    float orangeSignOpacityFL = 1;

    // Front Center
    float greenSignOpacityFC = 1;
    float orangeSignOpacityFC = 1;

    // Front Right
    float greenSignOpacityFR = 1;
    float orangeSignOpacityFR = 1;

    /**
     * ***** Back Sensors ******
     */
    // Back Left
    float greenSignOpacityBL = 1;
    float orangeSignOpacityBL = 1;

    // Back Center
    float greenSignOpacityBC = 1;
    float orangeSignOpacityBC = 1;

    // Back Right
    float greenSignOpacityBR = 1;
    float orangeSignOpacityBR = 1;

    //----------------------------------------------------------------
    /**
     * ******
     */
    /* Texts */
    /**
     * ******
     */
    Text startText;
    Text aboutText;
    Text aboutTextInLabel;
    Text motorTitle;
    Text greetingText;

    //----------------------------------------------------------------
    /**
     * *******
     */
    /* Labels */
    /**
     * *******
     */
    // Status Label
    Label speedLabelRPM;
    Label speedLabelKM;
    Label dateLabel;
    Label timeLabel;
    Label batteryLabel;

    //----------------------------------------------------------------
    /**
     * ********************
     */
    /*       Gauge         */
    /**
     * ********************
     */
    Gauge gauge;
    Gauge gaugeKM;

    //----------------------------------------------------------------
    /**
     * ********************
     */
    /*       Effects       */
    /**
     * ********************
     */
    Glow glow;
    Glow glowLabels;

    //----------------------------------------------------------------
    /**
     * ********************
     */
    /* Images & ImageViews */
    /**
     * ********************
     */
    /**
     * **************************
     */
    /**
     * *** Car Sensors Flags ****
     */
    /**
     * **************************
     */
    /**
     * ***** Front Sensors ******
     */
    // Front Left
    Image sensorGrnImgFL;
    ImageView sensorGrnImgViewFL;

    Image sensorOrgImgFL;
    ImageView sensorOrgImgViewFL;

    Image sensorRedImgFL;
    ImageView sensorRedImgViewFL;

    // Front Center
    Image sensorGrnImgFC;
    ImageView sensorGrnImgViewFC;

    Image sensorOrgImgFC;
    ImageView sensorOrgImgViewFC;

    Image sensorRedImgFC;
    ImageView sensorRedImgViewFC;

    // Front Right
    Image sensorGrnImgFR;
    ImageView sensorGrnImgViewFR;

    Image sensorOrgImgFR;
    ImageView sensorOrgImgViewFR;

    Image sensorRedImgFR;
    ImageView sensorRedImgViewFR;

    /**
     * ***** Back Sensors ******
     */
    // Back Left
    Image sensorGrnImgBL;
    ImageView sensorGrnImgViewBL;

    Image sensorOrgImgBL;
    ImageView sensorOrgImgViewBL;

    Image sensorRedImgBL;
    ImageView sensorRedImgViewBL;

    // Back Center
    Image sensorGrnImgBC;
    ImageView sensorGrnImgViewBC;

    Image sensorOrgImgBC;
    ImageView sensorOrgImgViewBC;

    Image sensorRedImgBC;
    ImageView sensorRedImgViewBC;

    // Back Right
    Image sensorGrnImgBR;
    ImageView sensorGrnImgViewBR;

    Image sensorOrgImgBR;
    ImageView sensorOrgImgViewBR;

    Image sensorRedImgBR;
    ImageView sensorRedImgViewBR;

    //----------------------------------------------------------------
    // Background    
    Image mainBackgroundImg;
    ImageView mainBackgroundImgView;

    // GIF
    Image greetingGifImg;
    ImageView greetingGifImgView;

    // Symbols
    Image backButtonImg;
    ImageView backButtonImgView;
    ImageView backButtonImgView2;

    Image iconImg;

    Image warningImg;
    ImageView warningImgView;

    // Car FrontView
    Image carTop;
    ImageView carTopView;

    // About Text Label
    Image aboutTextLabel;
    ImageView aboutTextLabelView;

    // Warning Label
    Image warningLabelImg;
    ImageView warningLabelImgView;

    //----------------------------------------------------------------
    /**
     * ***********
     */
    /* Animations */
    /**
     * ***********
     */
    // Opacity Animation
    AnimationTimer grntimer;
    AnimationTimer orgtimer;
    AnimationTimer time;

    //----------------------------------------------------------------
    /**
     * ******
     */
    /* Panes */
    /**
     * ******
     */
    // Start Pane
    StackPane startPane;

    // Main Pane
    StackPane mainPane;

    // About Pane
    StackPane aboutPane;

    //----------------------------------------------------------------
    /**
     * *******
     */
    /* Scenes */
    /**
     * *******
     */
    // Start Scene
    Scene startScene;

    // Motor Scene
    Scene motorScene;

    // About Scene
    Scene aboutScene;

    //----------------------------------------------------------------
    Thread SerialReadThread;
    Thread TimeLabelThread;
    Thread mainThread;

    RaspberryConnect RaspiConnect;
//    Connection class
//    Connect connection;
//    
//    
//    Thread backGroundSerial;
//    Thread wifi;

    //----------------------------------------------------------------
    float map(float x, float in_min, float in_max, float out_min, float out_max) {
        return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
    }

    /**
     * *************************************************************
     */
    /**
     * ********************** Initialization ***********************
     */
    /**
     * @throws
     * java.io.FileNotFoundException*************************************************************
     */
    @Override
    public void init() throws FileNotFoundException {

        dtf = DateTimeFormatter.ofPattern("dd-MM-yyyy");
        dtf2 = DateTimeFormatter.ofPattern("HH:mm:ss");
        T2 = LocalDateTime.now();

        /**
         * **************************
         */
        /* Flags & Numeric Variables */
        /**
         * **************************
         */
//        speedRPM = 0;  
//        speedKM = 0;
        //----------------------------------------------------------------
        /**
         * ********************
         */
        /*       Effects       */
        /**
         * ********************
         */
        // Glow
        glow = new Glow(3);
        glowLabels = new Glow(2);

        //----------------------------------------------------------------
        /**
         * ********************
         */
        /*       Gauge       */
        /**
         * ********************
         */
        gauge = new Gauge();
        gauge.setSkin(new SimpleDigitalSkin(gauge));
        gauge.setUnit("Rpm");  //unit
        gauge.setUnitColor(Color.WHITE);
        gauge.setValueVisible(false);
        gauge.setBarColor(Color.rgb(7, 137, 191));
        gauge.setNeedleColor(Color.rgb(194, 1, 54));
        gauge.setThresholdColor(Color.rgb(194, 1, 54));
        gauge.setThreshold(150);
        gauge.setThresholdVisible(true);
        gauge.setTickLabelColor(Color.WHITE);
        gauge.setTickMarkColor(Color.WHITE);
        gauge.setMaxSize(150, 150);
        gauge.setTranslateX(-200);
        gauge.setTranslateY(10);
        gauge.setMaxValue(251);

        gaugeKM = new Gauge();
        gaugeKM.setSkin(new SimpleDigitalSkin(gaugeKM));
        gaugeKM.setUnit("M/h\nx10");  //unit
        gaugeKM.setUnitColor(Color.WHITE);
        gaugeKM.setValueVisible(false);
        gaugeKM.setBarColor(Color.rgb(7, 137, 191));
        gaugeKM.setNeedleColor(Color.rgb(194, 1, 54));
        gaugeKM.setThresholdColor(Color.rgb(194, 1, 54));
        gaugeKM.setThreshold(200);
        gaugeKM.setThresholdVisible(true);
        gaugeKM.setTickLabelColor(Color.WHITE);
        gaugeKM.setTickMarkColor(Color.WHITE);
        gaugeKM.setMaxSize(150, 150);
        gaugeKM.setTranslateX(200);
        gaugeKM.setTranslateY(10);
        gaugeKM.setMaxValue(410);

        //----------------------------------------------------------------
        /**
         * ********************
         */
        /* Images & ImageViews */
        /**
         * ********************
         */
        mainBackgroundImg = new Image(getClass().getResourceAsStream("Images/mainBackground.png"));
        mainBackgroundImgView = new ImageView(mainBackgroundImg);
        mainBackgroundImgView.setFitHeight(480);
        mainBackgroundImgView.setFitWidth(800);

        greetingGifImg = new Image(getClass().getResourceAsStream("Images/greeting.gif"));
        greetingGifImgView = new ImageView(greetingGifImg);

        iconImg = new Image(getClass().getResourceAsStream("Images/Icon.png"));

        warningImg = new Image(getClass().getResourceAsStream("Images/warning.png"));
        warningImgView = new ImageView(warningImg);
        warningImgView.opacityProperty().set(warningSignOpacity);
        warningImgView.setFitHeight(135);
        warningImgView.setFitWidth(135);
        warningImgView.setTranslateX(588);
        warningImgView.setTranslateY(-145);

        carTop = new Image(getClass().getResourceAsStream("Images/CARTOP.png"));
        carTopView = new ImageView(carTop);
        carTopView.setTranslateX(-5);
        carTopView.setTranslateY(30);
        carTopView.setFitWidth(140);
        carTopView.setPreserveRatio(true);
        carTopView.setRotate(90);

        /**
         * ************** Car Sensors Images *************
         */
        grntimer = new grnTimer();
        orgtimer = new orgTimer();
        time = new Timer();

        /**
         * ***** Front Sensors ******
         */
        // Front Left
        sensorGrnImgFL = new Image(getClass().getResourceAsStream("Images/Sensor/green/greenSensorFrontLeft.png"));
        sensorGrnImgViewFL = new ImageView(sensorGrnImgFL);
        sensorGrnImgViewFL.opacityProperty().set(greenSignOpacityFL);
        sensorGrnImgViewFL.setTranslateX(0);
        sensorGrnImgViewFL.setTranslateY(25);
        sensorGrnImgViewFL.setFitWidth(185);
        sensorGrnImgViewFL.setPreserveRatio(true);

        sensorOrgImgFL = new Image(getClass().getResourceAsStream("Images/Sensor/orange/orangeSensorFrontLeft.png"));
        sensorOrgImgViewFL = new ImageView(sensorOrgImgFL);
        sensorOrgImgViewFL.opacityProperty().set(orangeSignOpacityFL);
        sensorOrgImgViewFL.setTranslateX(0);
        sensorOrgImgViewFL.setTranslateY(25);
        sensorOrgImgViewFL.setFitWidth(185);
        sensorOrgImgViewFL.setPreserveRatio(true);

        sensorRedImgFL = new Image(getClass().getResourceAsStream("Images/Sensor/red/redSensorFrontLeft.png"));
        sensorRedImgViewFL = new ImageView(sensorRedImgFL);
        sensorRedImgViewFL.setTranslateX(0);
        sensorRedImgViewFL.setTranslateY(25);
        sensorRedImgViewFL.setFitWidth(185);
        sensorRedImgViewFL.setPreserveRatio(true);

        // Front Center
        sensorGrnImgFC = new Image(getClass().getResourceAsStream("Images/Sensor/green/greenSensorFrontCenter.png"));
        sensorGrnImgViewFC = new ImageView(sensorGrnImgFC);
        sensorGrnImgViewFC.opacityProperty().set(greenSignOpacityFC);
        sensorGrnImgViewFC.setTranslateX(0);
        sensorGrnImgViewFC.setTranslateY(25);
        sensorGrnImgViewFC.setFitWidth(185);
        sensorGrnImgViewFC.setPreserveRatio(true);

        sensorOrgImgFC = new Image(getClass().getResourceAsStream("Images/Sensor/orange/orangeSensorFrontCenter.png"));
        sensorOrgImgViewFC = new ImageView(sensorOrgImgFC);
        sensorOrgImgViewFC.opacityProperty().set(orangeSignOpacityFC);
        sensorOrgImgViewFC.setTranslateX(0);
        sensorOrgImgViewFC.setTranslateY(25);
        sensorOrgImgViewFC.setFitWidth(185);
        sensorOrgImgViewFC.setPreserveRatio(true);

        sensorRedImgFC = new Image(getClass().getResourceAsStream("Images/Sensor/red/redSensorFrontCenter.png"));
        sensorRedImgViewFC = new ImageView(sensorRedImgFC);
        sensorRedImgViewFC.setTranslateX(0);
        sensorRedImgViewFC.setTranslateY(25);
        sensorRedImgViewFC.setFitWidth(185);
        sensorRedImgViewFC.setPreserveRatio(true);

        // Front Right
        sensorGrnImgFR = new Image(getClass().getResourceAsStream("Images/Sensor/green/greenSensorFrontRight.png"));
        sensorGrnImgViewFR = new ImageView(sensorGrnImgFR);
        sensorGrnImgViewFR.opacityProperty().set(greenSignOpacityFR);
        sensorGrnImgViewFR.setTranslateX(0);
        sensorGrnImgViewFR.setTranslateY(25);
        sensorGrnImgViewFR.setFitWidth(185);
        sensorGrnImgViewFR.setPreserveRatio(true);

        sensorOrgImgFR = new Image(getClass().getResourceAsStream("Images/Sensor/orange/orangeSensorFrontRight.png"));
        sensorOrgImgViewFR = new ImageView(sensorOrgImgFR);
        sensorOrgImgViewFR.opacityProperty().set(orangeSignOpacityFR);
        sensorOrgImgViewFR.setTranslateX(0);
        sensorOrgImgViewFR.setTranslateY(25);
        sensorOrgImgViewFR.setFitWidth(185);
        sensorOrgImgViewFR.setPreserveRatio(true);

        sensorRedImgFR = new Image(getClass().getResourceAsStream("Images/Sensor/red/redSensorFrontRight.png"));
        sensorRedImgViewFR = new ImageView(sensorRedImgFR);
        sensorRedImgViewFR.setTranslateX(0);
        sensorRedImgViewFR.setTranslateY(25);
        sensorRedImgViewFR.setFitWidth(185);
        sensorRedImgViewFR.setPreserveRatio(true);

        /**
         * ***** Back Sensors ******
         */
        // Back Left
        sensorGrnImgBL = new Image(getClass().getResourceAsStream("Images/Sensor/green/greenSensorBackLeft.png"));
        sensorGrnImgViewBL = new ImageView(sensorGrnImgBL);
        sensorGrnImgViewBL.opacityProperty().set(greenSignOpacityBL);
        sensorGrnImgViewBL.setTranslateX(0);
        sensorGrnImgViewBL.setTranslateY(25);
        sensorGrnImgViewBL.setFitWidth(185);
        sensorGrnImgViewBL.setPreserveRatio(true);

        sensorOrgImgBL = new Image(getClass().getResourceAsStream("Images/Sensor/orange/orangeSensorBackLeft.png"));
        sensorOrgImgViewBL = new ImageView(sensorOrgImgBL);
        sensorOrgImgViewBL.opacityProperty().set(orangeSignOpacityBL);
        sensorOrgImgViewBL.setTranslateX(0);
        sensorOrgImgViewBL.setTranslateY(25);
        sensorOrgImgViewBL.setFitWidth(185);
        sensorOrgImgViewBL.setPreserveRatio(true);

        sensorRedImgBL = new Image(getClass().getResourceAsStream("Images/Sensor/red/redSensorBackLeft.png"));
        sensorRedImgViewBL = new ImageView(sensorRedImgBL);
        sensorRedImgViewBL.setTranslateX(0);
        sensorRedImgViewBL.setTranslateY(25);
        sensorRedImgViewBL.setFitWidth(185);
        sensorRedImgViewBL.setPreserveRatio(true);

        // Back Center
        sensorGrnImgBC = new Image(getClass().getResourceAsStream("Images/Sensor/green/greenSensorBackCenter.png"));
        sensorGrnImgViewBC = new ImageView(sensorGrnImgBC);
        sensorGrnImgViewBC.opacityProperty().set(greenSignOpacityBC);
        sensorGrnImgViewBC.setTranslateX(0);
        sensorGrnImgViewBC.setTranslateY(25);
        sensorGrnImgViewBC.setFitWidth(185);
        sensorGrnImgViewBC.setPreserveRatio(true);

        sensorOrgImgBC = new Image(getClass().getResourceAsStream("Images/Sensor/orange/orangeSensorBackCenter.png"));
        sensorOrgImgViewBC = new ImageView(sensorOrgImgBC);
        sensorOrgImgViewBC.opacityProperty().set(orangeSignOpacityBC);
        sensorOrgImgViewBC.setTranslateX(0);
        sensorOrgImgViewBC.setTranslateY(25);
        sensorOrgImgViewBC.setFitWidth(185);
        sensorOrgImgViewBC.setPreserveRatio(true);

        sensorRedImgBC = new Image(getClass().getResourceAsStream("Images/Sensor/red/redSensorBackCenter.png"));
        sensorRedImgViewBC = new ImageView(sensorRedImgBC);
        sensorRedImgViewBC.setTranslateX(0);
        sensorRedImgViewBC.setTranslateY(25);
        sensorRedImgViewBC.setFitWidth(185);
        sensorRedImgViewBC.setPreserveRatio(true);

        // Back Right
        sensorGrnImgBR = new Image(getClass().getResourceAsStream("Images/Sensor/green/greenSensorBackRight.png"));
        sensorGrnImgViewBR = new ImageView(sensorGrnImgBR);
        sensorGrnImgViewBR.opacityProperty().set(greenSignOpacityBR);
        sensorGrnImgViewBR.setTranslateX(0);
        sensorGrnImgViewBR.setTranslateY(25);
        sensorGrnImgViewBR.setFitWidth(185);
        sensorGrnImgViewBR.setPreserveRatio(true);

        sensorOrgImgBR = new Image(getClass().getResourceAsStream("Images/Sensor/orange/orangeSensorBackRight.png"));
        sensorOrgImgViewBR = new ImageView(sensorOrgImgBR);
        sensorOrgImgViewBR.opacityProperty().set(orangeSignOpacityBR);
        sensorOrgImgViewBR.setTranslateX(0);
        sensorOrgImgViewBR.setTranslateY(25);
        sensorOrgImgViewBR.setFitWidth(185);
        sensorOrgImgViewBR.setPreserveRatio(true);

        sensorRedImgBR = new Image(getClass().getResourceAsStream("Images/Sensor/red/redSensorBackRight.png"));
        sensorRedImgViewBR = new ImageView(sensorRedImgBR);
        sensorRedImgViewBR.setTranslateX(0);
        sensorRedImgViewBR.setTranslateY(25);
        sensorRedImgViewBR.setFitWidth(185);
        sensorRedImgViewBR.setPreserveRatio(true);

        //----------------------------------------------------------------    
        // Warning Label
        warningLabelImg = new Image(getClass().getResourceAsStream("Images/warningLabel.png"));
        warningLabelImgView = new ImageView(warningLabelImg);
        warningLabelImgView.setFitHeight(230);
        warningLabelImgView.setFitWidth(500);
        warningLabelImgView.setTranslateX(580);
        warningLabelImgView.setTranslateY(-150);

        //----------------------------------------------------------------
        /**
         * ******
         */
        /* Texts */
        /**
         * ******
         */
        // Greeting Text
        greetingText = new Text("... Click Anywhere to Skip ...");
        greetingText.setFont(Font.font("Verdana", 12));
        greetingText.setFill(Color.WHITE);
        greetingText.setTranslateY(200);

        // Status Label
        speedLabelRPM = new Label();
        speedLabelRPM.setTextFill(Color.WHITE);
        speedLabelRPM.setFont(Font.font("Arial", 40));
        speedLabelRPM.setCache(true);
        speedLabelRPM.setEffect(glow);
        speedLabelRPM.setTranslateX(-200);

        speedLabelKM = new Label("0");
        speedLabelKM.setTextFill(Color.WHITE);
        speedLabelKM.setFont(Font.font("Arial", 40));
        speedLabelKM.setCache(true);
        speedLabelKM.setEffect(glow);
        speedLabelKM.setTranslateX(200);

        dateLabel = new Label("" + (dtf.format(T2)) + "");
        dateLabel.setTextFill(Color.WHITE);
        dateLabel.setFont(Font.font("Arial", 12));
        dateLabel.setCache(true);
        dateLabel.setEffect(glowLabels);
        dateLabel.setTranslateY(-120);

        batteryLabel = new Label("100%");
        batteryLabel.setTextFill(Color.WHITE);
        batteryLabel.setFont(Font.font("Arial", 12));
        batteryLabel.setCache(true);
        batteryLabel.setEffect(glowLabels);
        batteryLabel.setTranslateY(-120);
        batteryLabel.setTranslateX(-127);

        timeLabel = new Label();
        timeLabel.setTextFill(Color.WHITE);
        timeLabel.setFont(Font.font("Arial", 12));
        timeLabel.setCache(true);
        timeLabel.setEffect(glowLabels);
        timeLabel.setTranslateY(-120);
        timeLabel.setTranslateX(130);
        time.start();

        //----------------------------------------------------------------
        /**
         * ******
         */
        /* Panes */
        /**
         * ******
         */
        mainPane = new StackPane();
        mainPane.getChildren().add(mainBackgroundImgView);
        mainPane.getChildren().add(carTopView);
        mainPane.getChildren().add(gauge);
        mainPane.getChildren().add(gaugeKM);
        mainPane.getChildren().add(speedLabelRPM);
        mainPane.getChildren().add(speedLabelKM);

        mainPane.getChildren().add(sensorRedImgViewFL);
        mainPane.getChildren().add(sensorOrgImgViewFL);
        mainPane.getChildren().add(sensorGrnImgViewFL);

        mainPane.getChildren().add(sensorRedImgViewFC);
        mainPane.getChildren().add(sensorOrgImgViewFC);
        mainPane.getChildren().add(sensorGrnImgViewFC);

        mainPane.getChildren().add(sensorRedImgViewFR);
        mainPane.getChildren().add(sensorOrgImgViewFR);
        mainPane.getChildren().add(sensorGrnImgViewFR);

        mainPane.getChildren().add(sensorRedImgViewBL);
        mainPane.getChildren().add(sensorOrgImgViewBL);
        mainPane.getChildren().add(sensorGrnImgViewBL);

        mainPane.getChildren().add(sensorRedImgViewBC);
        mainPane.getChildren().add(sensorOrgImgViewBC);
        mainPane.getChildren().add(sensorGrnImgViewBC);

        mainPane.getChildren().add(sensorRedImgViewBR);
        mainPane.getChildren().add(sensorOrgImgViewBR);
        mainPane.getChildren().add(sensorGrnImgViewBR);

        mainPane.getChildren().add(dateLabel);
        mainPane.getChildren().add(batteryLabel);
        mainPane.getChildren().add(timeLabel);
        mainPane.getChildren().add(greetingGifImgView);
        mainPane.getChildren().add(greetingText);

        //----------------------------------------------------------------
        motorScene = new Scene(mainPane, 800, 480);

        //----------------------------------------------------------------
        RaspiConnect = new RaspberryConnect();
        ReadDataTask();
        mainTask();

    }

    public void mainTask() {
        Runnable MT = () -> {
            while (true) {

                if ((US_FL < 100) || (US_FC < 100) || (US_FR < 100) || (US_BL < 100) || (US_BC < 100) || (US_BR < 100)) {
                    grntimer.start();
                } else {

                }

                if ((US_FL < 50) || (US_FC < 50) || (US_FR < 50) || (US_BL < 50) || (US_BC < 50) || (US_BR < 50)) {
                    orgtimer.start();
                } else {

                }
                speedRPM = Motor_Rpm;
                speedKM = (int)(((speedRPM * 27) / 1000.0) * 60);
                Platform.runLater(
                        () -> {
                            speedLabelRPM.setText("" + speedRPM + "");
                            speedLabelKM.setText("" + speedKM + "");
                        }
                );

                gauge.setValue(speedRPM);
                gaugeKM.setValue(speedKM);
                try {
                    mainThread.sleep(5000);
                } catch (InterruptedException ex) {
                    Logger.getLogger(GUI.class.getName()).log(Level.SEVERE, null, ex);
                }

            }
        };
        mainThread = new Thread(MT);
        mainThread.start();
    }

    /**
     * *************************************************************
     */
    /**
     * ********************** Start Function ***********************
     */
    /**
     * @param stage*************************************************************
     */
    @Override
    public void start(Stage stage) {

        // Handlers
        EventHandler<MouseEvent> eventHandler = (MouseEvent e) -> {
            mainPane.getChildren().remove(greetingGifImgView);
            mainPane.getChildren().remove(greetingText);
        };

        greetingGifImgView.addEventFilter(MouseEvent.MOUSE_CLICKED, eventHandler);

        stage.setOnCloseRequest((WindowEvent e) -> {
            Platform.exit();
            System.exit(0);
        });

        //----------------------------------------------------------------
        /**
         * **************
         */
        /* Scene & Stage */
        /**
         * **************
         */
        stage.setTitle("Motor Controller");
        stage.getIcons().add(iconImg);
        stage.setResizable(true);
        stage.setScene(motorScene);
        stage.initStyle(StageStyle.UNDECORATED);
        stage.show();

        //----------------------------------------------------------------
    }

    public void ReadDataTask() {
        Runnable task = () -> {
            while (true) {
            
//                  Motor_Rpm++;
                    RecievedData = (byte) RaspiConnect.RaspberryReadData();
                    if (RecievedData != -1) {
                        System.out.println("State: " + State);
                        switch (State) {
                            case 0:
                                if (RecievedData == 'W') {
                                    State++;
                                    System.out.println("WEGZ_State");

                                }
                                break;
                            case 1:

                                switch (RecievedData) {
                                    case 0x51:
                                        DesiredData = RecievedData;
                                        wegz = (int) DesiredData;
                                        State++;
                                        System.out.println("WEGZ_FL " + wegz);

                                        break;
                                    case 0x52:
                                        DesiredData = RecievedData;
                                        wegz = (int) DesiredData;
                                        State++;
                                        System.out.println("WEGZ_FC " + wegz);

                                        break;
                                    case 0x53:
                                        DesiredData = RecievedData;
                                        wegz = (int) DesiredData;
                                        State++;
                                        System.out.println("WEGZ_FR " + wegz);
                                        break;
                                    case 0x61:
                                        DesiredData = RecievedData;
                                        wegz = (int) DesiredData;
                                        State++;
                                        System.out.println("WEGZ_BL " + wegz);
                                        break;
                                    case 0x62:
                                        DesiredData = RecievedData;
                                        wegz = (int) DesiredData;
                                        State++;
                                        System.out.println("WEGZ_BC " + wegz);
                                        break;
                                    case 0x63:
                                        DesiredData = RecievedData;
                                        wegz = (int) DesiredData;
                                        State++;
                                        System.out.println("WEGZ_BR " + wegz);
                                        ;
                                        break;
                                    case 0x71:
                                        DesiredData = RecievedData;
                                        State++;
                                        wegz = (int) DesiredData;
                                        System.out.println("WEGZ_RPM " + wegz);
                                        break;
                                    default:
                                        State--;
                                        break;
                                }
                                break;
                            case 2:
                                switch (DesiredData) {
                                    case 0x51:
                                        US_FL = RecievedData;
                                        wegz = (int) RecievedData;
                                        System.out.println("valu_FL " + wegz);
                                        break;
                                    case 0x52:
                                        US_FC = RecievedData;
                                        wegz = (int) RecievedData;
                                        System.out.println("val_Fc " + wegz);
                                        break;
                                    case 0x53:
                                        US_FR = RecievedData;
                                        wegz = (int) RecievedData;
                                        System.out.println("val_Fr " + wegz);
                                        break;
                                    case 0x61:
                                        US_BL = RecievedData;
                                        wegz = (int) RecievedData;
                                        System.out.println("WEGZ_bL " + wegz);
                                        break;
                                    case 0x62:
                                        US_BC = RecievedData;
                                        wegz = (int) RecievedData;
                                        System.out.println("WEGZ_bc " + wegz);
                                        break;
                                    case 0x63:
                                        US_BR = RecievedData;
                                        wegz = (int) RecievedData;
                                        System.out.println("WEGZ_br " + wegz);
                                        break;
                                    case 0x71:
                                        Motor_Rpm = RecievedData;
                                        wegz = (int) RecievedData;
                                        System.out.println("WEGZ_RPM " + wegz);
                                    default:
                                        break;
                                }
                                State = 0;
                                break;

                        }
                    }
                    
            }

        };

        SerialReadThread = new Thread(task);
        SerialReadThread.start();

    }

    private class grnTimer extends AnimationTimer {

        @Override
        public void handle(long now) {

            Handle();
        }

        private void Handle() {

            greenSignOpacityBC = map(US_BC, 50, 100, 0, 1);
            sensorGrnImgViewBC.opacityProperty().set(greenSignOpacityBC);

            greenSignOpacityBL = map(US_BL, 50, 100, 0, 1);
            sensorGrnImgViewBL.opacityProperty().set(greenSignOpacityBL);

            greenSignOpacityBR = map(US_BR, 50, 100, 0, 1);
            sensorGrnImgViewBR.opacityProperty().set(greenSignOpacityBR);

            greenSignOpacityFC = map(US_FC, 50, 100, 0, 1);
            sensorGrnImgViewFC.opacityProperty().set(greenSignOpacityFC);

            greenSignOpacityFR = map(US_FR, 50, 100, 0, 1);
            sensorGrnImgViewFR.opacityProperty().set(greenSignOpacityFR);

            greenSignOpacityFL = map(US_FL, 50, 100, 0, 1);
            sensorGrnImgViewFL.opacityProperty().set(greenSignOpacityFL);

        }
    }

    private class orgTimer extends AnimationTimer {

        @Override
        public void handle(long now) {

            Handle();
        }

        private void Handle() {

            orangeSignOpacityBC = map(US_BC, 10, 50, 0, 1);
            sensorOrgImgViewBC.opacityProperty().set(orangeSignOpacityBC);

            orangeSignOpacityBL = map(US_BL, 10, 50, 0, 1);
            sensorOrgImgViewBL.opacityProperty().set(orangeSignOpacityBL);

            orangeSignOpacityBR = map(US_BR, 10, 50, 0, 1);
            sensorOrgImgViewBR.opacityProperty().set(orangeSignOpacityBR);

            orangeSignOpacityFC = map(US_FC, 10, 50, 0, 1);
            sensorOrgImgViewFC.opacityProperty().set(orangeSignOpacityFC);

            orangeSignOpacityFR = map(US_FR, 10, 50, 0, 1);
            sensorOrgImgViewFR.opacityProperty().set(orangeSignOpacityFR);

            orangeSignOpacityFL = map(US_FL, 10, 50, 0, 1);
            sensorOrgImgViewFL.opacityProperty().set(orangeSignOpacityFL);
        }
    }

    private class Timer extends AnimationTimer {

        @Override
        public void handle(long now) {

            Handle();
        }

        private void Handle() {
            T1 = LocalDateTime.now();
            timeLabel.setText("" + (dtf2.format(T1)) + "");

        }
    }

    /**
     * *************************************************************
     */
    /**
     * ********************** Main Function ************************
     */
    /**
     * @param args*************************************************************
     */
    public static void main(String[] args) {

        Application.launch(args);
    }

}
