package com.example.jnifirstapplication;

import java.io.Serializable;

public enum EnumStudent implements Serializable {
    PARTHIV(123),
    DIVYA(12345),
    RAVI(564);

    private final int value;

    EnumStudent(int value) {
        this.value = value;
    }

    public int getValue() {
        return value;
    }
}

