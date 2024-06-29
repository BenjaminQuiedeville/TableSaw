using ACME
using GLMakie
using FFTW


function generate_circuit(low = 0.5, high = 0.5)

    circ = @circuit begin
        
        input = voltagesource()
        power_supply = voltagesource()

        output = voltageprobe()

        input_res = resistor(3.3e3)
        low_pot1 = resistor(10e3 * (1 - low))
        low_pot2 = resistor(10e3 * low)
        high_pot1 = resistor(10e3 * (1 - high))
        high_pot2 = resistor(10e3 * high)

        output_buffer_opamp = opamp()
        output_buffer_res = resistor(3.3e3)

        output_cap = capacitor(10e-6)

        filter1_res1 = resistor(100e3)
        filter1_res2 = resistor(330)
        filter1_cap1 = capacitor(68e-9)
        filter1_cap2 = capacitor(1.5e-6)
        filter1_opamp = opamp()

        filter2_res1 = resistor(100e3)
        filter2_res2 = resistor(330)
        filter2_cap1 = capacitor(4.7e-9)
        filter2_cap2 = capacitor(0.1e-6)
        filter2_opamp = opamp()

        filter3_res1 = resistor(82e3)
        filter3_res2 = resistor(330)
        filter3_cap1 = capacitor(6.8e-9)
        filter3_cap2 = capacitor(0.15e-6)
        filter3_opamp = opamp()


        # main part
        input[+] == input_res[1]
        input[-] == gnd
        input_res[2] == low_pot1[1] == high_pot1[1] == output_buffer_opamp["in+"]
        output_buffer_opamp["out-"] == gnd
        output_buffer_opamp["out+"] == output_cap[1] == output_buffer_res[2]
        output_buffer_res[1] == output_buffer_opamp["in-"] == low_pot2[2] == high_pot2[2]
        
        output_cap[2] == output[+]
        output[-] == gnd
        

        power_supply[+] == filter1_res1[1] == filter2_res1[1] == filter3_res1[1]
        power_supply[-] == gnd

        # filter1
        filter1_res1[2] == filter1_opamp["in+"] == filter1_cap1[1]
        filter1_opamp["out+"] == filter1_opamp["in-"] == filter1_res2[1]
        filter1_opamp["out-"] == gnd
        filter1_cap1[2] == filter1_res2[2] == filter1_cap2[1]
        filter1_cap2[2] == low_pot1[2] == low_pot2[1]

        # filter2
        filter2_res1[2] == filter2_opamp["in+"] == filter2_cap1[1]
        filter2_opamp["out+"] == filter2_opamp["in-"] == filter2_res2[1]
        filter2_opamp["out-"] == gnd
        filter2_cap1[2] == filter2_res2[2] == filter2_cap2[1]
        filter2_cap2[2] == high_pot1[2] == high_pot2[1]

        # filter3
        filter3_res1[2] == filter3_opamp["in+"] == filter3_cap1[1]
        filter3_opamp["out+"] == filter3_opamp["in-"] == filter3_res2[1]
        filter3_opamp["out-"] == gnd
        filter3_cap1[2] == filter3_res2[2] == filter3_cap2[1]
        filter3_cap2[2] == high_pot1[2] == high_pot2[1]
    end

    return circ
end


function main() 
    samplerate = 44100.0

    circuit = generate_circuit(0.2, 0.2)
    model = DiscreteModel(circuit, 1/samplerate)
    
    nFreq = 2^14
    signals = [1 zeros(1, nFreq - 1); 
               4.5 * ones(1, nFreq)]

    y = run!(model, signals)[1, :]

    ySpectre = 20 * log10.((y |> rfft .|> abs).^2)
    yFreqs = rfftfreq(size(y)[1], samplerate) .+ 1.0
    
    fig = Figure()
    ax = Axis(fig[1, 1], xscale = log10)
    lines!(ax, yFreqs, ySpectre)

    display(fig)

    return nothing
end 
main()