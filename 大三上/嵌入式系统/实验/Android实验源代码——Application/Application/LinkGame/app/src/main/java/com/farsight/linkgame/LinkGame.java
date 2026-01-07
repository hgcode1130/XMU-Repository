package com.farsight.linkgame;

import android.app.Activity;
import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.os.Bundle;
import android.view.Display;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.Window;
import android.view.WindowManager;
import android.widget.AbsoluteLayout;
import android.widget.TableLayout;
import android.widget.TableRow;
import java.util.ArrayList;

@SuppressWarnings("deprecation")

class Point extends androidx.appcompat.widget.AppCompatImageView
{
	public int x, y;
	public int imgId;
	public Point(Context context) {
		super(context);
		// TODO Auto-generated constructor stub
	}
	public Point(Context context, int x, int y){
		super(context);
		this.x = x;
		this.y = y;
	}
	public Point(Context context, int x, int y, int imgId){
		super(context);
		this.x = x;
		this.y = y;
		this.imgId = imgId;
		this.setImageResource(imgId);
	}
	public void setImageId(int imgId){
		this.setImageResource(imgId);
	}
}

class Link {
	private static int ROW, COLUMN, SREEN_H, SREEN_W;
	private Point p1 = null, p2 = null;
	private ArrayList<Integer> picIdMap = new ArrayList<Integer>();
	private int[] picIdAry = new int[LinkGame.MAXPICNUM];
	private int PICNUM = 15;
	private Point[][] matrix = new Point[16][12];
	private int[][] line = new int[4][2];
	private Context context;
	public Link(Context contxt, int row, int column, int sreen_h, int screen_w){
		this.context = contxt;
		Link.ROW = row;
		Link.COLUMN = column;
		Link.SREEN_H = sreen_h;
		Link.SREEN_W = screen_w;
	}
	public void setContext(Context contxt){
		this.context = contxt;
	}
	public boolean isPnt1Pressed(){
		if(p1 != null)
			return true;
		else
			return false;
	}
	public boolean setPicIdAry(int idx, int value){
		picIdAry[idx] = value;
		return true;
	}
	public boolean paintPad(){
		int i = 0, pidId, j, range;
		Point pnt;
		for(i = 0; i < (ROW * COLUMN)/2; i++){
			pidId = picIdAry[(int)(Math.random()* PICNUM)];
			picIdMap.add(new Integer(pidId));
			picIdMap.add(new Integer(pidId));
		}
		for( i = 1; i <= ROW; i++){
			for(j = 1; j <= COLUMN; j++){
				range = picIdMap.size();
				int rnd = (int)(Math.random()* range);
				int tmp = picIdMap.remove(rnd);
				pnt = new Point(context, j, i, tmp);
				pnt.setOnClickListener(new OnClickListener(){
				
					public void onClick(View arg0) {
						if(matrix[((Point)arg0).y][((Point)arg0).x] == null){
							return ;
						}
						if(!isPnt1Pressed()){
							p1 = (Point)arg0;
							p1.setBackgroundColor(Color.LTGRAY);
						}
						else{
							p2 = (Point)arg0;
							if(p1 == p2)
								return ;
							if((p1.imgId == p2.imgId) && LinkPnt(p1, p2)){
								LinkGame.padLay.setLine(line[0], line[1], line[2], line[3]);
								p1.setVisibility(4);
								p2.setVisibility(4);
								matrix[p1.y][p1.x] = null;
								matrix[p2.y][p2.x] = null;
								p1 = null;
								p2 = null;
							}else{
								p1.setBackgroundColor(Color.TRANSPARENT);
								p1 = p2;
								p1.setBackgroundColor(Color.LTGRAY);
								p2 = null;
							}
						}
					}
        		});
				matrix[i][j] = pnt;
			}
		}
		return true;
	}
	
	public Point getPoint(int r, int c){
		return matrix[r][c];
	}
	
	public boolean LineX(int x, int y, int xt){   
		int i;
        for( i = x; i != xt;){
        	if(i <= COLUMN + 1){
        		if(matrix[y][i] != null){   
        			return false;   
        		} 
        	}
            if(x < xt)
            	i++;
            else
            	i--;
        }   
        return true;   
    }   
	
	public boolean LineY(int x, int y, int yt){   
		int i;
        for( i = y; i != yt; ){   
        	if(i <= ROW + 1){
        		if(matrix[i][x] != null){   
                	return false;   
            	}
        	}
            if(y < yt)
            	i++;
            else
            	i--;
        }   
        return true;   
    }   
	
	public boolean LinkPnt(Point P1, Point P2){   
        //P1在P2下方，交换P1、P2,保证P1一直在P2的上方
		Point P3;
		int j;
		int xPadding = (SREEN_W - COLUMN*LinkGame.PIC_SIZE)/2 - LinkGame.PIC_SIZE*3/2 + LinkGame.PIC_SIZE;
		int yPadding = (SREEN_H - ROW*LinkGame.PIC_SIZE)/2 - LinkGame.PIC_SIZE*3/2 + LinkGame.PIC_SIZE;
        if(P1.y > P2.y){   
            P3 = P1;   
            P1 = P2;   
            P2 = P3;   
        }   
        //P1下方1点（y+1）先纵向再横向是否可连接。（因为起点P1不为空，所以检测其下方一点）   
        if( LineY(P1.x, (P1.y+1), P2.y) && LineX(P1.x, P2.y, P2.x) ) {
        	line[0][0] = xPadding + LinkGame.PIC_SIZE * P1.x;
        	line[0][1] = yPadding + LinkGame.PIC_SIZE * P1.y;
        	if(p1.x != p2.x){
            	line[1][0] = xPadding + LinkGame.PIC_SIZE * P1.x;
            	line[1][1] = yPadding + LinkGame.PIC_SIZE * P2.y;
	        	line[2][0] = xPadding + LinkGame.PIC_SIZE * P2.x;
	        	line[2][1] = yPadding + LinkGame.PIC_SIZE * P2.y;
        	}else{
            	line[1][0] = xPadding + LinkGame.PIC_SIZE * P2.x;
            	line[1][1] = yPadding + LinkGame.PIC_SIZE * P2.y;
        	}
        	return true;  
        }
        	  
        //循环从P1点开始向左逐列向下纵向检测连接P2，如果纵向可连接再横向向右检测
        for(j = (P1.x-1); j >= 0; j--){   
            if( matrix[P1.y][j] != null ) break;   
            if( LineY(j, (P1.y+1), P2.y) && LineX(j, P2.y, P2.x) ) {
            	line[0][0] = xPadding + LinkGame.PIC_SIZE * P1.x;
            	line[0][1] = yPadding + LinkGame.PIC_SIZE * P1.y;
            	line[1][0] = xPadding + LinkGame.PIC_SIZE * j;
            	line[1][1] = yPadding + LinkGame.PIC_SIZE * P1.y;
            	line[2][0] = xPadding + LinkGame.PIC_SIZE * j;
            	line[2][1] = yPadding + LinkGame.PIC_SIZE * P2.y;
            	line[3][0] = xPadding + LinkGame.PIC_SIZE * P2.x;
            	line[3][1] = yPadding + LinkGame.PIC_SIZE * P2.y;
            	return true;  
            }
        }   
        //循环从P1点开始向右逐列向下纵向检测连接P2，如果纵向可连接再横向向右检测
        for( j = (P1.x+1); j <= COLUMN + 1; j++){   
            if( matrix[P1.y][j] != null ) break;   
            if( LineY(j, (P1.y+1), P2.y) && LineX(j, P2.y, P2.x) ) {
            	line[0][0] = xPadding + LinkGame.PIC_SIZE * P1.x;
            	line[0][1] = yPadding + LinkGame.PIC_SIZE * P1.y;
            	line[1][0] = xPadding + LinkGame.PIC_SIZE * j;
            	line[1][1] = yPadding + LinkGame.PIC_SIZE * P1.y;
            	line[2][0] = xPadding + LinkGame.PIC_SIZE * j;
            	line[2][1] = yPadding + LinkGame.PIC_SIZE * P2.y;
            	line[3][0] = xPadding + LinkGame.PIC_SIZE * p2.x;
            	line[3][1] = yPadding + LinkGame.PIC_SIZE * P2.y;
            	return true;  
            } 
        }   
        //P1在P2右侧，交换P1、P2,保证P1一直在P2的左侧
        if(P1.x > P2.x){   
            P3 = P1;   
            P1 = P2;   
            P2 = P3;   
        }   
        //P1右方1点（x+1）先横向向右再纵向是否可连接。（因为起点P1不为空，所以检测其右方一点）   
        if( LineX((P1.x+1), P1.y, P2.x) && LineY(P2.x, P1.y, P2.y) ) {
        	line[0][0] = xPadding + LinkGame.PIC_SIZE * P1.x;
        	line[0][1] = yPadding + LinkGame.PIC_SIZE * P1.y;
        	if(p1.y != p2.y){
            	line[1][0] = xPadding + LinkGame.PIC_SIZE * P2.x;
            	line[1][1] = yPadding + LinkGame.PIC_SIZE * P1.y;
            	line[2][0] = xPadding + LinkGame.PIC_SIZE * P2.x;
            	line[2][1] = yPadding + LinkGame.PIC_SIZE * P2.y;
        	}else{
            	line[1][0] = xPadding + LinkGame.PIC_SIZE * P2.x;
            	line[1][1] = yPadding + LinkGame.PIC_SIZE * P2.y;
        	}
        	return true;  
        }   
        //循环从P1点开始向上逐行横向向右检测，如果横向可连接再纵向向下检测
        for(j = (P1.y-1); j >= 0; j--){   
            if( matrix[j][P1.x] != null ) break;   
            if( LineX((P1.x+1), j, P2.x) && LineY(P2.x, j, P2.y) ) {
            	line[0][0] = xPadding + LinkGame.PIC_SIZE * P1.x;
            	line[0][1] = yPadding + LinkGame.PIC_SIZE * P1.y;
            	line[1][0] = xPadding + LinkGame.PIC_SIZE * P1.x;
            	line[1][1] = yPadding + LinkGame.PIC_SIZE * j;
            	line[2][0] = xPadding + LinkGame.PIC_SIZE * P2.x;
            	line[2][1] = yPadding + LinkGame.PIC_SIZE * j;
            	line[3][0] = xPadding + LinkGame.PIC_SIZE * P2.x;
            	line[3][1] = yPadding + LinkGame.PIC_SIZE * P2.y;
            	return true;  
            }   
        }
        //循环从P1点开始向下逐行横向向右检测，如果横向可连接再纵向向下检测
        for(j = (P1.y+1); j <= ROW + 1; j++){   
            if( matrix[j][P1.x] != null ) break;   
            if( LineX((P1.x+1), j, P2.x) && LineY(P2.x, j, P2.y) ) {
            	line[0][0] = xPadding + LinkGame.PIC_SIZE * P1.x;
            	line[0][1] = yPadding + LinkGame.PIC_SIZE * P1.y;
            	line[1][0] = xPadding + LinkGame.PIC_SIZE * P1.x;
            	line[1][1] = yPadding + LinkGame.PIC_SIZE * j;
            	line[2][0] = xPadding + LinkGame.PIC_SIZE * P2.x;
            	line[2][1] = yPadding + LinkGame.PIC_SIZE * j;
            	line[3][0] = xPadding + LinkGame.PIC_SIZE * P2.x;
            	line[3][1] = yPadding + LinkGame.PIC_SIZE * P2.y;
            	return true;  
            }      
        }   
        return false;   
    }   
}

class GamePad extends View
{
	private int[][] point = new int[4][2];
	private Paint paint= new Paint();
	public GamePad(Context context) {
		super(context);
    	paint.setColor(Color.WHITE);
    	paint.setStrokeWidth(1);
		// TODO Auto-generated constructor stub
	}
	public void setLine(int[] p1, int[] p2, int[] p3, int[] p4){
		point[0] = p1;
		point[1] = p2;
		point[2] = p3;
		point[3] = p4;
	}
	protected void onDraw(Canvas canvas) {
		if(point[0][0] != 0 && point[1][0] != 0)
			canvas.drawLine(point[0][0], point[0][1], point[1][0], point[1][1], paint);
		if(point[1][0] != 0 && point[2][0] != 0)
			canvas.drawLine(point[1][0], point[1][1], point[2][0], point[2][1], paint);
		if(point[2][0] != 0 && point[3][0] != 0)
			canvas.drawLine(point[2][0], point[2][1], point[3][0], point[3][1], paint);
		for(int i = 0; i < 4; i++)
			for(int j = 0; j < 2; j++){
				point[i][j] = 0;
			}
		invalidate();
    }
}

public class LinkGame extends Activity 
{
    /** Called when the activity is first created. */
	public static final int MAXPICNUM = 20, PIC_SIZE = 30;
	private int height, width, lrPadding, tbPadding;
    public static GamePad padLay ;
    @SuppressWarnings("deprecation")
	public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        // full screen with title
        getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,  WindowManager.LayoutParams.FLAG_FULLSCREEN);
        // full screen without title
        requestWindowFeature(Window.FEATURE_NO_TITLE);   
        Display display = getWindowManager().getDefaultDisplay(); 
        height = display.getHeight();
        width = display.getWidth();

        int row = 14;
        int column = 6;
        Link lk = new Link(this, row, column, height, width);
        lk.setPicIdAry(0, R.drawable.p1);
        lk.setPicIdAry(1, R.drawable.p2);
        lk.setPicIdAry(2, R.drawable.p3);
        lk.setPicIdAry(3, R.drawable.p4);
        lk.setPicIdAry(4, R.drawable.p5);
        lk.setPicIdAry(5, R.drawable.p6);
        lk.setPicIdAry(6, R.drawable.p7);
        lk.setPicIdAry(7, R.drawable.p8);
        lk.setPicIdAry(8, R.drawable.p9);
        lk.setPicIdAry(9, R.drawable.p10);
        lk.setPicIdAry(10, R.drawable.p11);
        lk.setPicIdAry(11, R.drawable.p12);
        lk.setPicIdAry(12, R.drawable.p13);
        lk.setPicIdAry(13, R.drawable.p14);
        lk.setPicIdAry(14, R.drawable.p15);
        lk.setPicIdAry(15, R.drawable.p16);
        lk.setPicIdAry(16, R.drawable.p17);
        lk.setPicIdAry(17, R.drawable.p18);
        lk.setPicIdAry(18, R.drawable.p19);
        lk.setPicIdAry(19, R.drawable.p20);
        lk.paintPad();
        //abLay.setBackgroundColor(Color.YELLOW);
        AbsoluteLayout mainLay = new AbsoluteLayout(this);
        padLay = new GamePad(this);
        //LinearLayout lineLay = new LinearLayout(this);
        lrPadding = (width - column*30)/2;
        tbPadding = (height - row*30)/2;
        TableLayout tbLay = new TableLayout(this);
        tbLay.setBackgroundColor(Color.TRANSPARENT);
        int i, j;
        Point pnt;
        for(i = 1; i <= row; i++){
        	TableRow tbRow = new TableRow(this);
        	for(j = 1; j <= column; j++){
        		pnt = lk.getPoint(i, j);
        		tbRow.addView(pnt);
        	}
        	tbLay.addView(tbRow);
        }
        AbsoluteLayout.LayoutParams tvLP = new AbsoluteLayout.LayoutParams(column*30, row*30, lrPadding, tbPadding);
        mainLay.addView(padLay);
        mainLay.addView(tbLay, tvLP);
        mainLay.setBackgroundResource(R.drawable.apple);
        setContentView(mainLay);
    }
}