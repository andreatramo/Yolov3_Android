package uk.lcas.andreatramo.yolov3_objectdetector;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;
import org.opencv.imgcodecs.Imgcodecs;

import org.opencv.core.Mat;

import android.annotation.SuppressLint;
import android.content.Context;
import android.content.res.AssetManager;


import java.io.BufferedInputStream;
import java.io.File;
import java.io.FileOutputStream;
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

        String rootPath = getFilesDir().getPath();

        // Example of a call to a native method
        TextView tv = (TextView) findViewById(R.id.sample_text);
        tv.setText("GOOOOOOO");

        String cfg_file = getPath(".cfg", this.getApplicationContext());
        String weigth_file = getPath(".weights", this.getApplicationContext());
        float conf_thr = 0.5f;
        String classNames_file = getPath(".names", this.getApplicationContext());
        String img_file = getPath(".jpg", this.getApplicationContext());


        create(cfg_file, weigth_file, conf_thr, classNames_file);

        Mat input_frame = Imgcodecs.imread(img_file); //the frame to send to classify

        Mat output_frame = new Mat();

        classify(input_frame.getNativeObjAddr(), output_frame.getNativeObjAddr());

    }

    @SuppressLint("LongLogTag")
    private static String getPath(String fileType, Context context) {
        AssetManager assetManager = context.getAssets();
        String[] pathNames = {};
        String fileName = "";
        System.out.println("-----------------------------------------------------------------------");
        try {
            pathNames = assetManager.list("");
        } catch (IOException e) {
            e.printStackTrace();
        }
        for ( String filePath : pathNames ) {
            System.out.println(filePath);
            if ( filePath.endsWith(fileType)) {
                fileName = filePath;
                break;
            }
        }
        BufferedInputStream inputStream;
        try {
            // Read data from assets.
            inputStream = new BufferedInputStream(assetManager.open(fileName));
            byte[] data = new byte[inputStream.available()];
            inputStream.read(data);
            inputStream.close();

            // Create copy file in storage.
            File outFile = new File(context.getFilesDir(), fileName);
            FileOutputStream os = new FileOutputStream(outFile);
            os.write(data);
            os.close();
            // Return a path to file which may be read in common way.
            return outFile.getAbsolutePath();
        } catch (IOException ex) {
            //Log.i(TAG, "Failed to upload a file");
        }
        return "";
    }

    public native void create(String cfg_file, String weights_file, float conf_thr, String classNames_file);

    public native void classify(long input_frame, long output_frame);

}
