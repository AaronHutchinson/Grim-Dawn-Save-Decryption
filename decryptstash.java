import java.util.List;
import java.util.ArrayList;
import java.util.Arrays;
import java.io.IOException;
import java.io.FileInputStream;
import java.io.FileOutputStream;

public class decryptstash
{
	static class block
	{
		int len;
		int end;
	}

	static class stash_file
	{
		private int key;
		private int[] table = new int[256];
		private byte[] buf = new byte[32];
		private int pos;

		String mod;
		List<sack> sacks;

		private int get() throws IOException
		{
			if (pos >= buf.length)
				throw new IOException();

			return buf[pos++] & 0xFF;
		}

		private void put(int val)
		{
			int len = buf.length;

			if (pos >= len)
			{
				buf = Arrays.copyOf(buf, Math.max(len << 1, pos + 1));
			}

			buf[pos++] = (byte)val;
		}

		private void read_key() throws IOException
		{
			int k = get();
			k |= get() << 8;
			k |= get() << 16;
			k |= get() << 24;

			k ^= 0x55555555;

			key = k;

			for (int i = 0; i < 256; i++)
			{
				k = Integer.rotateRight(k, 1);
				k *= 39916801;
				table[i] = k;
			}
		}

		private int next_int() throws IOException
		{
			int ret = get();
			ret |= get() << 8;
			ret |= get() << 16;
			ret |= get() << 24;

			ret ^= key;

			return ret;
		}

		int read_int() throws IOException
		{
			int k = key;

			int val = get();
			k ^= table[val];

			int b = get();
			k ^= table[b];
			val |= b << 8;

			b = get();
			k ^= table[b];
			val |= b << 16;

			b = get();
			k ^= table[b];
			val |= b << 24;

			val ^= key;

			key = k;

			return val;
		}

		int read_byte() throws IOException
		{
			int b = get();
			int ret = (b ^ key) & 0xFF;
			key ^= table[b];
			return ret;
		}

		float read_float() throws IOException
		{
			return Float.intBitsToFloat(read_int());
		}

		String read_str() throws IOException
		{
			int len = read_int();

			StringBuilder sb = new StringBuilder(len);

			for (int i = 0; i < len; i++)
			{
				sb.append((char)read_byte());
			}

			return sb.toString();
		}

		int read_block_start(block b) throws IOException
		{
			int ret = read_int();

			b.len = next_int();
			b.end = pos + b.len;

			return ret;
		}

		void read_block_end(block b) throws IOException
		{
			if (pos != b.end)
				throw new IOException();

			if (next_int() != 0)
				throw new IOException();
		}

		void write_int(int val)
		{
			put(val);
			put(val >> 8);
			put(val >> 16);
			put(val >> 24);
		}

		void write_byte(int val)
		{
			put(val);
		}

		void write_float(float val)
		{
			write_int(Float.floatToIntBits(val));
		}

		void write_str(String str)
		{
			int len = str != null ? str.length() : 0;

			write_int(len);

			for (int i = 0; i < len; i++)
			{
				write_byte(str.charAt(i));
			}
		}

		void write_block_start(block b, int n)
		{
			write_int(n);
			write_int(0);
			b.end = pos;
		}

		void write_block_end(block b)
		{
			int cur = pos;

			pos = b.end - 4;
			write_int(cur - b.end);

			pos = cur;
			write_int(0);
		}

		void read(String filename) throws IOException
		{
			FileInputStream file = new FileInputStream(filename);
			buf = new byte[(int)file.getChannel().size()];
			pos = 0;
			file.read(buf);
			file.close();

			read_key();

			if (read_int() != 2)
				throw new IOException();

			block b = new block();

			if (read_block_start(b) != 18)
				throw new IOException();

			if (read_int() != 4) // version
				throw new IOException();

			if (next_int() != 0)
				throw new IOException();

			mod = read_str();

			int n = read_int();

			sacks = new ArrayList<sack>(n);

			for (int i = 0; i < n; i++)
			{
				sack bag = new sack();
				bag.read(this);
				sacks.add(bag);
			}

			read_block_end(b);
		}

		void write(String filename) throws IOException
		{
			pos = 0;

			write_int(0x55555555);
			write_int(2);

			block b = new block();
			write_block_start(b, 18);

			write_int(4); // version;
			write_int(0);
			write_str(mod);

			write_int(sacks.size());

			for (sack bag : sacks)
			{
				bag.write(this);
			}

			write_block_end(b);

			FileOutputStream file = new FileOutputStream(filename);
			file.write(buf, 0, pos);
			file.close();
		}
	}

	static class sack
	{
		List<item> items;
		int width;
		int height;

		void read(stash_file stash) throws IOException
		{
			block b = new block();
			stash.read_block_start(b);

			width = stash.read_int();
			height = stash.read_int();

			int n = stash.read_int();

			items = new ArrayList<item>(n);

			for (int i = 0; i < n; i++)
			{
				item it = new item();
				it.read(stash);
				items.add(it);
			}

			stash.read_block_end(b);
		}

		void write(stash_file stash)
		{
			block b = new block();
			stash.write_block_start(b, 0);

			stash.write_int(width);
			stash.write_int(height);

			stash.write_int(items.size());

			for (item it : items)
			{
				it.write(stash);
			}

			stash.write_block_end(b);
		}
	}

	static class item
	{
		public String baseName;
		public String prefixName;
		public String suffixName;
		public String modifierName;
		public String transmuteName;
		public int seed;
		public String relicName;
		public String relicBonus;
		public int relicSeed;
		public String augmentName;
		public int unknown;
		public int augmentSeed;
		public int var1;
		public int stackCount;
		public float xOffset;
		public float yOffset;

		public void read(stash_file stash) throws IOException
		{
			baseName = stash.read_str();
			prefixName = stash.read_str();
			suffixName = stash.read_str();
			modifierName = stash.read_str();
			transmuteName = stash.read_str();
			seed = stash.read_int();
			relicName = stash.read_str();
			relicBonus = stash.read_str();
			relicSeed = stash.read_int();
			augmentName = stash.read_str();
			unknown = stash.read_int();
			augmentSeed = stash.read_int();
			var1 = stash.read_int();
			stackCount = stash.read_int();
			xOffset = stash.read_float();
			yOffset = stash.read_float();
		}

		public void write(stash_file stash)
		{
			stash.write_str(baseName);
			stash.write_str(prefixName);
			stash.write_str(suffixName);
			stash.write_str(modifierName);
			stash.write_str(transmuteName);
			stash.write_int(seed);
			stash.write_str(relicName);
			stash.write_str(relicBonus);
			stash.write_int(relicSeed);
			stash.write_str(augmentName);
			stash.write_int(unknown);
			stash.write_int(augmentSeed);
			stash.write_int(var1);
			stash.write_int(stackCount);
			stash.write_float(xOffset);
			stash.write_float(yOffset);
		}
	}

	public static void main(String[] args)
	{
		if (args.length != 2)
		{
			System.err.println("Usage: java decryptstash <in file> <out file>");
			return;
		}

		stash_file stash = new stash_file();

		try
		{
			stash.read(args[0]);
		}
		catch (Exception e)
		{
			System.err.printf("Error reading file: %s\n", args[0]);
			return;
		}

		try
		{
			stash.write(args[1]);
		}
		catch (Exception e)
		{
			System.err.printf("Error writing file: %s\n", args[1]);
			return;
		}
	}
}