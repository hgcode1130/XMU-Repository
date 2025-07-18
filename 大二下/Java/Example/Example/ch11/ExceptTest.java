/**
 @version 1.31 2000-07-13
 @author Cay Horstmann
 */
package ch11;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.io.*;

public class ExceptTest {
	public static void main(String[] args) {
		ExceptTestFrame frame = new ExceptTestFrame();
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.show();
	}
}

/**
 * A frame with a panel for testing various exceptions
 */
class ExceptTestFrame extends JFrame {
	public ExceptTestFrame() {
		setTitle("ExceptTest");
		Container contentPane = getContentPane();
		ExceptTestPanel panel = new ExceptTestPanel();
		contentPane.add(panel);
		pack();
	}
}

/**
 * A panel with radio buttons for running code snippets and studying their
 * exception behavior
 */
class ExceptTestPanel extends Box {
	public ExceptTestPanel() {
		super(BoxLayout.Y_AXIS);
		group = new ButtonGroup();

		Font f = new Font("Serif", Font.PLAIN, 30);

		UIManager.put("RadioButton.font", f);
		UIManager.put("TextField.font", f);

		// add radio buttons for code snippets

		addRadioButton("Integer divide by zero", new ActionListener() {
			public void actionPerformed(ActionEvent event) {
				a[1] = 1 / (a.length - a.length);
			}
		});

		addRadioButton("Floating point divide by zero", new ActionListener() {
			public void actionPerformed(ActionEvent event) {
				a[1] = a[2] / (a[3] - a[3]);
			}
		});

		addRadioButton("Array bounds", new ActionListener() {
			public void actionPerformed(ActionEvent event) {
				a[1] = a[10];
			}
		});

		addRadioButton("Bad cast", new ActionListener() {
			public void actionPerformed(ActionEvent event) {
				a = (double[]) event.getSource();
			}
		});

		addRadioButton("Null pointer", new ActionListener() {
			public void actionPerformed(ActionEvent event) {
				event = null;
				System.out.println(event.getSource());
			}
		});

		addRadioButton("sqrt(-1)", new ActionListener() {
			public void actionPerformed(ActionEvent event) {
				a[1] = Math.sqrt(-1);
			}
		});

		addRadioButton("No such file", new ActionListener() {
			public void actionPerformed(ActionEvent event) {
				try {
					FileInputStream is = new FileInputStream("No such file");
				} catch (IOException exception) {
					textField.setText(exception.toString());
				}
			}
		});

		addRadioButton("Throw unknown", new ActionListener() {
			public void actionPerformed(ActionEvent event) {
				throw new UnknownError();
			}
		});

		// add the text field for exception display
		textField = new JTextField(30);
		add(textField);
	}

	/**
	 * Adds a radio button with a given listener to the panel. Traps any
	 * exceptions in the actionPerformed method of the listener.
	 * 
	 * @param s
	 *            the label of the radio button
	 * @param listener
	 *            the action listener for the radio button
	 */
	private void addRadioButton(String s, ActionListener listener) {
		JRadioButton button = new JRadioButton(s, false) {
			// the button calls this method to fire an
			// action event. We override it to trap exceptions
			protected void fireActionPerformed(ActionEvent event) {
				try {
					textField.setText("No exception");
					super.fireActionPerformed(event);
				} catch (Exception exception) {
					textField.setText(exception.toString());
				}
			}
		};

		button.addActionListener(listener);
		add(button);
		group.add(button);
	}

	private ButtonGroup group;

	private JTextField textField;

	private double[] a = new double[10];
}
