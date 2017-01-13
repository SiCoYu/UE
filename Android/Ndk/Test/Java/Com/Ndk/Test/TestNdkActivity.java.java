package Com.Ndk.Test;

import android.app.Activity;
import android.os.Bundle;
import android.widget.TextView;

public class TestNdkActivity extends Activity {
    static {
        System.loadLibrary("TestNdk");
    }

    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
		//setContentView(R.layout.main);
        
        //第一个方法传入的两个参数没有做操作，直接返回hello jni，不用管
        String str = JniClient.AddStr("test", "test");
        
        //第二个方法暂时不实现
        //  int iSum = JniClient.AddInt(5, 2);        
		// String strSum = "5 + 7 = " + iSum;
        
        TextView tv1 = new TextView(this);
        tv1.setText(str);
        setContentView(tv1);
    }
}