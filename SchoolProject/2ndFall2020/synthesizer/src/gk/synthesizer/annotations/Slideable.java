package gk.synthesizer.annotations;

public @interface Slideable {
    int minValue() default 0;

    int MaxValue() default 0;

    int defaultValue() default 0;
}
