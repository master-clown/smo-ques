function plot_data

    data = importdata('sol.txt', ' ', 1);
    num_col = size(data.data, 2);
    
    hold on;
    for j = 2:num_col
        plot(data.data(:, 1), data.data(:, j));
    end
    legend(data.colheaders(2:end));
end