function plot_data

    data = dlmread('sol.txt');
    num_col = size(data, 2);
    
    hold on;
    for j = 2:num_col
        plot(data(:, 1), data(:, j));
    end
end