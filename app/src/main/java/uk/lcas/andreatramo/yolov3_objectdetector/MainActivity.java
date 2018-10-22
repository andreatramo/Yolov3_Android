package uk.lcas.andreatramo.yolov3_objectdetector;

import android.os.Environment;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;
import org.opencv.imgcodecs.Imgcodecs;

import android.content.res.AssetManager;


import org.opencv.core.Mat;

import java.io.File;
import java.io.IOException;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("yolo");
    }


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        TextView tv = (TextView) findViewById(R.id.sample_text);
        tv.setText("Noooooo!!!");

        File file = Environment.getExternalStorageDirectory();
        String root = file.getAbsolutePath();
        String path = "./assets/yolo_config/yolov3-tiny.cfg";
        tv.setText(path);


        String cfg_file = "./assets/yolo_config/yolov3-tiny.cfg";
        String weigth_file = root + "/assets/yolo_config/yolov3-tiny.weigth";
        float conf_thr = 0.5f;
        String classNames_file = root + "/assets/yolo_config/coco.names";

        create(cfg_file, weigth_file, conf_thr, classNames_file);

        Mat input_frame = Imgcodecs.imread(root + "/assets/data/aeroplane.jpg"); //the frame to send to classify
        Imgcodecs.imwrite(root + "/assets/data/aeroplane_2.jpg", input_frame);

        Mat output_frame = new Mat();

        //classify(input_frame.getNativeObjAddr(), output_frame.getNativeObjAddr());

    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */

    public native void create(String cfg_file, String weights_file, float conf_thr, String classNames_file);

    public native void classify(long input_frame, long output_frame);

}
