package com.example.nametodolist;

import androidx.appcompat.app.AppCompatActivity;

import android.app.AlertDialog;
import android.content.DialogInterface;
import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.EditText;
import android.widget.ListView;
import android.widget.TextView;

import java.util.ArrayList;
import java.util.List;

/**
 * Roman Soldatov BS19-02
 * Exercise 1
 */
public class MainActivity extends AppCompatActivity {

    private List<String> taskList;
    private ArrayAdapter<String> mAdapter;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        taskList = new ArrayList<>();

        ListView mTaskListView = findViewById(R.id.list_todo);

        mAdapter = new ArrayAdapter<>(this, R.layout.todo_item, R.id.task_title, taskList);
        mTaskListView.setAdapter(mAdapter);
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.main_menu, menu);
        return super.onCreateOptionsMenu(menu);
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        switch (item.getItemId()) {
            case R.id.action_add_task:
                Log.d("MainClass", "Add a new task");
                addNewTask();
                return true;
            default:
                return super.onOptionsItemSelected(item);
        }
    }

    private void addNewTask() {
        final EditText taskEditText = new EditText(this);
        AlertDialog dialog = new AlertDialog.Builder(this)
                .setTitle("Add a new task")
                .setMessage("What do you want to do next?")
                .setView(taskEditText)
                .setPositiveButton("Add", new DialogInterface.
                        OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        String task = String.valueOf(taskEditText.getText());
                        Log.d("MainClass", "Task to add: " + task);
                        addItem(task);
                    }
                }).setNegativeButton("Cancel", null)
                .create();

        dialog.show();
    }

    public void editTask(View editButton) {
        String taskCurrentText = getTextView(editButton);

        final EditText taskEditText = new EditText(this);
        taskEditText.setText(taskCurrentText);

        AlertDialog dialog = new AlertDialog.Builder(this)
                .setTitle("Edit task")
                .setMessage("Rename the task")
                .setView(taskEditText)
                .setPositiveButton("Save", (dialog1, which) -> {
                    String taskNewText = String.valueOf(taskEditText.getText());
                    setItem(taskCurrentText, taskNewText);
                }).setNegativeButton("Cancel", null)
                .create();
        dialog.show();
    }

    public void deleteTask(View deleteButton) {
        removeItem(getTextView(deleteButton));
    }

    private String getTextView(View view) {
        TextView textView = ((View) view.getParent()).findViewById(R.id.task_title);
        return String.valueOf(textView.getText());
    }

    private void addItem(String itemText) {
        taskList.add(itemText);
        mAdapter.notifyDataSetChanged();
    }

    private void setItem(String currentItem, String newItemText) {
        taskList.set(taskList.indexOf(currentItem), newItemText);
        mAdapter.notifyDataSetChanged();
    }

    private void removeItem(String itemText) {
        taskList.remove(itemText);
        mAdapter.notifyDataSetChanged();
    }
}