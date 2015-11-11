package com.example.backoff_tts;

import android.support.v7.app.ActionBarActivity;
import android.support.v7.app.ActionBar;
import android.support.v4.app.Fragment;
import android.content.res.AssetManager;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.EditText;
import android.os.Build;

import java.io.IOException;
import java.io.InputStream;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class MainActivity extends ActionBarActivity {
	EditText inputText;
    Button execute;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        if (savedInstanceState == null) {
            getFragmentManager().beginTransaction()
                    .add(R.id.container, new Fragment())
                    .commit();
        }
        
        inputText = (EditText) findViewById(R.id.input);
        execute = (Button) findViewById(R.id.synth);

        public void insert_substring(String a, String b, int position)
        {
        		      StringBuffer sb = new StringBuffer(a);
        		      sb.insert(position,b);
        		      //System.out.println(sb);
        }
        public int check2(String syl , int found){
        	char[] temp=syl.toCharArray();
        	int flag=0;
        	if(temp[syl.length()-1]== 'w' && found==0)
        	{
       B: 		temp[syl.length()-1] = 'b';
        		found=check1(temp,found);
        		flag=1;
        	}
        	if(temp[syl.length()-1]=='b' && found==0)
        	{
        		temp[syl.length()-1]='m';
        		found=check1(temp,found);
        	}
        	if(temp[syl.length()-1]=='m' && found==0)
        	{
        		temp[syl.length()-1]='l';
        		found=check1(temp,found);
        	}
        	if(found==0)
        	{
        		temp[syl.length()-1]='w';
        		found=check1(temp,found);
        		if(found==0 && flag==0)
        			break B;
        	}
        	return found;
        }
        
        
        
        System.out.println("jks");
execute.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) 
            {
            	String str = inputText.getText().toString();
            	int k=0;
            	AssetManager assetManager = getAssets();
            	InputStream input;
                String phoneset;
                String syllables;
                int size;
                phoneset = "ppp";
                syllables = "sss";
                
                try {
                		   input = assetManager.open("Telugu_PhoneSet_Hts.txt");
                		   size = input.available();
                		   byte[] buffer = new byte[size];
                		   input.read(buffer);
                		   input.close();
                		   phoneset = new String(buffer);
                		   //System.out.println(phoneset);
              	          
                	} catch (IOException e) {
                	e.printStackTrace();
                	}
                
                try {
         		   input = assetManager.open("syllables.txt");
         		   size = input.available();
         		   byte[] buffer = new byte[size];
         		   input.read(buffer);
         		   input.close();
         		   syllables = new String(buffer);	 
        	       //System.out.println(syllables);
         	} catch (IOException e) {
         	e.printStackTrace();
         	}
                //System.out.println(phoneset);
                //System.out.println(syllables);
               /////////////////////////////////////////////////// 
                int BUFSIZE,i,count=0,pos=0, found=0, dec=0,flag,j,prev,l,epos_i=0,len,flag1,cluster;
            	int vow_i=0, sym_i=0, quant_i=0, phone_i=0,cnst_i=0;
            	int[] epos = new int[10];
            	
            	short[] final1 = new short[1000];
            	String syl, syl_cpy, temp, input1; //input1=input
				String[] phoneset1 = new String [1000];
				String[] vow = new String [1000];
				String[] sym = new String [1000];
				String[] const1 = new String [1000];//const1=const
				String[] temp4 = new String [1000];
				String[] str1 = new String [1000]; //str1=str
				String[] temp5 = new String [30];
				String[] temp6 = new String [30];
				String[] temp7 = new String [30];
				String[] quantifier = new String [1000];
				String st,phn,quant;
				String temp1,temp2, temp3,v; //actually char
            	
				class queue {
					  public static int in;
					  public static int out;
					  String[] s = new String [1000];
					  public queue( int in, int out){
					    this.in = in;
					    this.out = out;
					    this.s = s;
					  }
					}
				queue.in=0;
				queue.out=-1;
				
				File lang_file = new File("phoneset.txt");
				try {

			        //Scanner sc = new Scanner(lang_file);
			        Scanner sc = new Scanner(lang_file).useDelimiter("\t");
			        while (sc.hasNextLine()) {
			        	phn=sc.next();
			        	temp2=sc.next();
			        	quant=sc.next();
			        	temp3=sc.next();
			        	if(quant.equals("VOW")){
			        		vow=phn;
			        	}
			        	}
			        	
			          //  int i = sc.nextInt();
			            System.out.println(i);
			        }
			        sc.close();
			    } 
			    catch (FileNotFoundException e) {
			        e.printStackTrace();
			    }
				
            	
            	//////////////////////////////////////////////
     /*       	String res = tts (str,syllables,phoneset);
            		
            	System.out.println(res);
            	
            	System.out.println("ijcklsd");*/
            }
        });
    }
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);

		if (savedInstanceState == null) {
			getSupportFragmentManager().beginTransaction()
					.add(R.id.container, new PlaceholderFragment()).commit();
		}
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {

		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

	@Override
	public boolean onOptionsItemSelected(MenuItem item) {
		// Handle action bar item clicks here. The action bar will
		// automatically handle clicks on the Home/Up button, so long
		// as you specify a parent activity in AndroidManifest.xml.
		int id = item.getItemId();
		if (id == R.id.action_settings) {
			return true;
		}
		return super.onOptionsItemSelected(item);
	}

	/**
	 * A placeholder fragment containing a simple view.
	 */
	public static class PlaceholderFragment extends Fragment {

		public PlaceholderFragment() {
		}

		@Override
		public View onCreateView(LayoutInflater inflater, ViewGroup container,
				Bundle savedInstanceState) {
			View rootView = inflater.inflate(R.layout.fragment_main, container,
					false);
			return rootView;
		}
	}

}
