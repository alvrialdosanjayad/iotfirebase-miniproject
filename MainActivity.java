package com.example.iot_firebase;

import androidx.appcompat.app.AppCompatActivity;
import androidx.annotation.NonNull;

import android.os.Bundle;
import android.widget.TextView;
import android.widget.ToggleButton;
import android.widget.CompoundButton;

import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;

public class MainActivity extends AppCompatActivity {
    ToggleButton buttonLampu;

    TextView cahaya;
    TextView jarak;

    String valueCahaya;
    String valueJarak;

    DatabaseReference dref;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        buttonLampu = (ToggleButton) findViewById(R.id.toggleButton_lampu1);

        cahaya = (TextView) findViewById(R.id.txtView_valueldr);
        jarak = (TextView) findViewById(R.id.txtView_valuejarak);


        dref = FirebaseDatabase.getInstance().getReference();
        dref.addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot dataSnapshot) {

                valueCahaya = dataSnapshot.child("Node1/cahaya").getValue().toString();
                cahaya.setText(valueCahaya);

                valueJarak = dataSnapshot.child("Node1/jarak").getValue().toString();
                jarak.setText(valueJarak);

            }

            @Override
            public void onCancelled(@NonNull DatabaseError databaseError) {

            }
        });

        buttonLampu.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                if(isChecked){
                    DatabaseReference lampu1Ref = FirebaseDatabase.getInstance().getReference("Node1/lampu");
                    lampu1Ref.setValue(1);
                }
                else
                {
                    DatabaseReference lampu1Ref = FirebaseDatabase.getInstance().getReference("Node1/lampu");
                    lampu1Ref.setValue(0);
                }
            }
        });
    }
}
